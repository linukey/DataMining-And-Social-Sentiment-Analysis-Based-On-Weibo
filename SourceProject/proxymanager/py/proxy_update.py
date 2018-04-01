#!/usr/bin/python3.5

from urllib import request, parse
import json
import os
import time
import requests

def get_proxy():
    url = 'http://api.xdaili.cn/xdaili-api//greatRecharge/getGreatIp?spiderId=017e7316994043838df880610211e716&orderno=YZ201711225665Md3vgz&returnType=2&count=5'
    proxy = []
    try:
        response = request.urlopen(url, timeout=10)
        result = response.read().decode('utf-8')
        jsondata = json.loads(result)
        for data in jsondata['RESULT']:
            proxy.append(data['ip'] + ":" + data['port'])
    except Exception as e:
        print('error')
        print(e)

    return proxy


def ip_available(proxy):
    server = proxy
    try:
        # install the opener
        opener = request.build_opener(request.ProxyHandler({'http':server}))
        #request.install_opener(opener)
        url = "http://www.baidu.com"
        #response = request.urlopen(url, timeout=3)
        response=opener.open(url, timeout=3)
        if response is not None:
            code = response.getcode()
            return code == 200
        else:
            return False

    except Exception as e:
        pass

    return False

# meet 20 available ip
def update_proxyfile(proxy_num, proxy_path):
    proxy_pool = set()
    
    # load the exists proxy
    os.system("echo \033[33m[ load the exisits proxy ]\033[0m")
    old_proxy = []
    file = open(proxy_path)
    for proxy in file.readlines():
        old_proxy.append(proxy)
    file.close()

    # test the exists proxy
    for proxy in old_proxy:
        proxy = proxy.split('\n')[0]
        if ip_available("http://" + proxy):
            proxy_pool.add(proxy)
            os.system("echo \033[32m[" + proxy + " is available!" + "]\033[0m")
        else:
            print(proxy + " is not available!")

    # request the new proxy and test the new proxy
    os.system("echo \033[33m[ request the new proxy ]\033[0m")
    number = 0;
    while len(proxy_pool) < proxy_num:
        number += 1;
        if number > 10:
            break
        # new_proxy
        new_proxy = get_proxy()
        for proxy in new_proxy:
            if len(proxy_pool) >= proxy_num:
                break
            if ip_available("http://" + proxy):
                proxy_pool.add(proxy)
                os.system("echo \033[32m[" + proxy + " is available!" + "]\033[0m")
            else:
                print(proxy + " is not available!")
                pass

        time.sleep(5)

    # write the proxy_result into proxy_ip
    file = open(proxy_path, 'w')
    for proxy in proxy_pool:
        file.write(proxy+'\n')
    file.close()
    print("\n\n")
    os.system("echo \033[32m[" + "update proxy success! respect proxy_cnt:" + str(proxy_num) + " actual proxy_cnt:" + str(len(proxy_pool)) + "]\033[0m")

    return len(proxy_pool)

if __name__ == '__main__':
    print(get_proxy())
