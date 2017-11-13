from weibo.items import WeiboCommentItem
from scrapy_redis.spiders import RedisSpider
from scrapy import Request
import json

'''
微博wise站点评论url样例：https://m.weibo.cn/api/comments/show?id=4160547165300149&page=1
url格式：https://m.weibo.cn/api/comments/show?id= [] &page= []
格式验证日期：2017.11.11
'''
class WeiboComment(RedisSpider):
    name = 'WeiboComment'
    redis_key = 'weibo_comment:start_urls'

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
            print(response.body)
            item = WeiboCommentItem()
            item['html'] = response.body
            yield item
            '''
            jsonData = json.loads(response.body.decode('utf-8'))
            item = WeiboCommentItem()
            for data in jsonData['data']:
                item['comment'] = data['text']
                item['phone'] = data['source']
                yield item
            '''

        #如果小于范围开始，去到开始的地方
        if number < range_start:
            number = range_start

        #向下扩展
        for i in range(3):
            next_url = url_pre + str(number+i+1)
            yield Request(next_url, callback=self.parse)
