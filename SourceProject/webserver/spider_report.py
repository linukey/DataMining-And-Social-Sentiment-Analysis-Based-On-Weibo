#!/usr/bin/python3.5
import urllib.request
from collections import OrderedDict
import uuid


def report(client_id, spidername, item_cnt):
    data = OrderedDict()
    data['client_id'] = str(client_id)
    data['spidername'] = spidername
    data['item_cnt'] = item_cnt

    request = urllib.request.Request(url="http://localhost:8001/update_spider", data=urllib.parse.urlencode(data).encode('utf-8'))
    response = urllib.request.urlopen(request)
    return response.read().decode('utf-8')


if __name__ == '__main__':
    print(report('123', 'weibo', '1'))

