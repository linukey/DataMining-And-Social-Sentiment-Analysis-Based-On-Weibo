# -*- coding: utf-8 -*-

#scrapy
BOT_NAME = 'weibo'

SPIDER_MODULES = ['weibo.spiders']
NEWSPIDER_MODULE = 'weibo.spiders'

ROBOTSTXT_OBEY = False
FEED_EXPORT_ENCODING = 'utf-8'
DOWNLOAD_DELAY = 3

DEFAULT_REQUEST_HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36',
    'Accept': 'image/webp,image/apng,image/*,*/*;q=0.8',
    'Accept-Language': 'zh-CN,zh;q=0.8,zh-TW;q=0.6',
    'Accept-Encoding': 'gzip, deflate, br'
}

ITEM_PIPELINES = {
    'weibo.pipelines.WeiboPipeline': 300,
}

#scrapy_redis
DUPEFILTER_CLASS = "scrapy_redis.dupefilter.RFPDupeFilter"
SCHEDULER = "scrapy_redis.scheduler.Scheduler"
SCHEDULER_PERSIST = True

REDIS_ITEMS_KEY = 'weibo:items'
REDIS_ITEMS_SERIALIZER = 'json.dumps'

#REDIS_HOST = 'rs'
#REDIS_PORT = '6379'

#crawl_range
RANGE_START = 1
RANGE_END = 100
