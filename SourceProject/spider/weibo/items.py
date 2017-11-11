# -*- coding: utf-8 -*-
import scrapy

class WeiboCommentItem(scrapy.Item):
    html = scrapy.Field()
