from weibo.items import WeiboItem
from scrapy_redis.spiders import RedisSpider
from scrapy import Request
import json

class WeiboRedis(RedisSpider):
    name = 'WeiboRedis'
    redis_key = 'weibo:start_urls'

    def __init__(self, *args, **kwargs):
        #domain = kwargs.pop('domain', '')
        #self.allowed_domains = filter(None, domain.split(','))
        super(WeiboRedis, self).__init__(*args, **kwargs)

    def parse(self, response):
        '''
        jsonData = json.loads(response.body)

        item = WeiboItem()
        for data in jsonData['data']:
            item['comment'] = data['text']
            item['phone'] = data['source']
            yield item

        url = response.url
        index = url[::-1].find('=')
        url_pre = url[:len(url)-index]
        url_pur = url[len(url)-index:]
        for i in range(3):
            next_url = url_pre + str(int(url_pur)+i+1)
            yield Request(next_url, callback=self.parse)
        '''
        item = WeiboItem()
        item['html'] = response.body
        return item
