#!/usr/bin/python3.5

import urllib.request
from collections import OrderedDict
import uuid

def get_ip(client_id):
    data = OrderedDict()
    data['client_id'] = str(client_id)
    data['exec'] = 'getproxy'

    request = urllib.request.Request(url="http://webserver:8001/get_proxy", data=urllib.parse.urlencode(data).encode('utf-8'))
    response = urllib.request.urlopen(request)
    return response.read().decode('utf-8')

if __name__ == '__main__':
    print(get_ip(uuid.uuid1()))
