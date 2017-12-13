#!/usr/bin/python3.5

import urllib.request
from collections import OrderedDict
import uuid
import _thread

def get_ip(client_id):
    data = OrderedDict()
    data['client_id'] = str(client_id)

    request = urllib.request.Request(url="http://localhost:8001/get_proxy", data=urllib.parse.urlencode(data).encode('utf-8'))
    response = urllib.request.urlopen(request)
    print(response.read().decode('utf-8'))


def get_task():
    data = OrderedDict()
    data['\n\n'] = '\n\n'

    request = urllib.request.Request(url="http://localhost:8001/get_task", data=urllib.parse.urlencode(data).encode('utf-8'))
    response = urllib.request.urlopen(request)
    print(response.read().decode('utf-8'))


if __name__ == '__main__':
    get_ip(uuid.uuid1())
    '''
    ids = []

    count = 1
    
    for i in range(count):
        ids.append(uuid.uuid1())
    
    for i in range(count):
        _thread.start_new_thread(get_ip, (ids[i],))

    while input():
        for i in range(count):
            _thread.start_new_thread(get_ip, (ids[i],))
    '''
