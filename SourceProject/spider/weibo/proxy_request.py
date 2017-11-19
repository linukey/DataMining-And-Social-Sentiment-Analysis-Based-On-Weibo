#!/usr/bin/python3.5

import urllib.request
from collections import OrderedDict
import uuid

def get_ip(client_id):
    data = OrderedDict()
    data['client_id'] = str(client_id)
    data['exec'] = 'getproxy'
    data['\n\n'] = '\n\n'

    request = urllib.request.Request(url="http://localhost:8001", data=urllib.parse.urlencode(data).encode('utf-8'))
    response = urllib.request.urlopen(request)
    return response.read().decode('utf-8')

if __name__ == '__main__':
    print(get_ip(uuid.uuid1()))
