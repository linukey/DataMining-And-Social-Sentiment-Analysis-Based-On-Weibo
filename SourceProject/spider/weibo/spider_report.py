#!/usr/bin/python3.5
import urllib.request
from collections import OrderedDict
import uuid
import time

def report(client_id, spidername, time, cnt):
    data = OrderedDict()
    data['client_id'] = str(client_id)
    data['spidername'] = spidername
    data['time'] = time
    data['cnt'] = cnt

    request = urllib.request.Request(url="http://webserver:8001/update_spider", data=urllib.parse.urlencode(data).encode('utf-8'))
    response = urllib.request.urlopen(request)
    return response.read().decode('utf-8')



if __name__ == '__main__':
    report('123', 'weibo', '1')

