import logging
import time
from scrapy.dupefilters import BaseDupeFilter
from scrapy.utils.request import request_fingerprint
from . import defaults
from .connection import get_redis_from_settings

logger = logging.getLogger(__name__)

class RFPDupeFilter(BaseDupeFilter):
    logger = logger

    def mylog(self, message):
        print("==================="+message+"====================")

    def __init__(self, server, key, debug=False):
        self.mylog("init")
        self.server = server
        self.key = key
        self.debug = debug
        self.logdupes = True

    def request_seen(self, request):
        self.mylog("request_seen")
        fp = self.request_fingerprint(request)
        added = self.server.sadd(self.key, fp)
        return added == 0

    def request_fingerprint(self, request):
        self.mylog("request_fingerprint")
        return request_fingerprint(request)

    @classmethod
    def from_settings(cls, settings):
        self.mylog("from_settings")
        server = get_redis_from_settings(settings)
        key = defaults.DUPEFILTER_KEY % {'timestamp': int(time.time())}
        debug = settings.getbool('DUPEFILTER_DEBUG')
        return cls(server, key=key, debug=debug)

    @classmethod
    def from_crawler(cls, crawler):
        self.mylog("from_crawler")
        return cls.from_settings(crawler.settings)

    @classmethod
    def from_spider(cls, spider):
        self.mylog("from_spider")
        settings = spider.settings
        server = get_redis_from_settings(settings)
        dupefilter_key = settings.get("SCHEDULER_DUPEFILTER_KEY", defaults.SCHEDULER_DUPEFILTER_KEY)
        key = dupefilter_key % {'spider': spider.name}
        debug = settings.getbool('DUPEFILTER_DEBUG')
        return cls(server, key=key, debug=debug)

    def close(self, reason=''):
        self.mylog("close")
        self.clear()

    def clear(self):
        self.mylog("clear")
        self.clear()
        self.server.delete(self.key)

    def log(self, request, spider):
        if self.debug:
            msg = "Filtered duplicate request: %(request)s"
            self.logger.debug(msg, {'request': request}, extra={'spider': spider})
        elif self.logdupes:
            msg = ("Filtered duplicate request %(request)s  - no more duplicates will be shown (see DUPEFILTER_DEBUG to show all duplicates)")
            self.logger.debug(msg, {'request': request}, extra={'spider': spider})
            self.logdupes = False
