#!/usr/bin/python3.5
import urllib.request
from collections import OrderedDict
import uuid
import time
import random


def report(client_id, spidername, time, cnt):
    data = OrderedDict()
    data['client_id'] = str(client_id)
    data['spidername'] = spidername
    data['time'] = time
    data['cnt'] = cnt

    request = urllib.request.Request(url="http://localhost:8001/update_spider", data=urllib.parse.urlencode(data).encode('utf-8'))
    response = urllib.request.urlopen(request)
    return response.read().decode('utf-8')


def get_task():
    request = urllib.request.Request(url="http://localhost:8001/get_task")
    response = urllib.request.urlopen(request)
    return response.read().decode('utf-8')


def simu_spider():
    while True:
        client = random.randint(1, 2)
        spidername = random.randint(1, 3)
        cnt = random.randint(1, 10)
        t = str(time.strftime('%Y/%m/%d %H:%M:%S',time.localtime(time.time())))

        print(report(client, spidername, t, cnt))
        print(get_task())

        time.sleep(5)


if __name__ == '__main__':
    simu_spider()
    #print(get_task())
