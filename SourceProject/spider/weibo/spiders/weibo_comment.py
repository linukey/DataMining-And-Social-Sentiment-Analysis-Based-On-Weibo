from weibo.items import WeiboCommentItem
from scrapy_redis.spiders import RedisSpider
from scrapy.spiders import Spider, CrawlSpider
from scrapy.exceptions import DontCloseSpider
from scrapy import signals
from scrapy import Request
import json
import warnings
import redis
from scrapy.utils.deprecate import method_is_overridden
from .. import defaults, connection

'''
微博wise站点评论url样例：https://m.weibo.cn/api/comments/show?id=4160547165300149&page=1
url格式：https://m.weibo.cn/api/comments/show?id= [] &page= []
格式验证日期：2017.11.11
'''
class WeiboComment(RedisSpider):
    name = 'WeiboComment'
    redis_key = 'weibo_comment:start_urls'
    dupefilter_key = 'weibo_comment:dupefilter'

    def __init__(self, *args, **kwargs):
        super(WeiboComment, self).__init__(*args, **kwargs)

    def parse(self, response):
        #控制爬行的范围
        range_start = int(self.settings.get('RANGE_START'))
        range_end = int(self.settings.get('RANGE_END'))

        #解析url
        url = response.url
        index = url[::-1].find('=')
        url_pre = url[:len(url)-index]
        number = int(url[len(url)-index:])

        #超出范围结束
        if range_end != -1 and number > range_end:
            return

        if number > range_start:
            item = WeiboCommentItem()
            item['html'] = response.body
            yield item

        #向下扩展
        try:
            rd = redis.StrictRedis(host='localhost', port=6379)
            i = 0
            n = 1
            while i < 2:
                if number+n >= range_end:
                    break
                next_url = url_pre + str(number+n)
                if rd.sadd(self.dupefilter_key, next_url) == 1:
                    rd.lpush(self.redis_key, next_url)
                    i += 1
                n += 1
        except:
            print('redis error')
