#!/usr/bin/python3.5

import urllib.request
from collections import OrderedDict
import uuid
import _thread

def get_ip(client_id):
    data = OrderedDict()
    data['client_id'] = str(client_id)
    data['exec'] = 'getproxy'
    data['\n\n'] = '\n\n'

    request = urllib.request.Request(url="http://localhost:8001", data=urllib.parse.urlencode(data).encode('utf-8'))
    response = urllib.request.urlopen(request)
    print(response.read().decode('utf-8'))

if __name__ == '__main__':
    ids = []
    
    for i in range(10):
        ids.append(uuid.uuid1())
    
    for i in range(10):
        _thread.start_new_thread(get_ip, (ids[i],))

    while input():
        for i in range(10):
            _thread.start_new_thread(get_ip, (ids[i],))
