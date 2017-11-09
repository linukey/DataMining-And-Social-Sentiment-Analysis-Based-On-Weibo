# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy

class WeiboItem(scrapy.Item):
    '''
    comment = scrapy.Field()
    phone = scrapy.Field()
    '''
    html = scrapy.Field()
