#!/usr/bin/python3.5

from urllib import request, parse
import json
import os
import time

def get_proxy():
    showapi_appid = "49824"
    showapi_sign = "6e1680fb4ab2468aac8e2c138b7b108a"

    url = "http://route.showapi.com/22-1"
    send_data = parse.urlencode([
        ('showapi_appid', showapi_appid),
        ('showapi_sign', showapi_sign)
    ])

    headers = {
        "User-Agent":"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36",
        "Accept-Language":"zh-CN,zh;q=0.8,zh-TW;q=0.6",
        "Accept-Encoding":"gzip, deflate, br",
        "Connection":"close"
    }

    proxy = []
     
    req = request.Request(url, headers=headers, data=send_data.encode('utf-8'))
    try:
        response = request.urlopen(req, timeout=10)
        result = response.read().decode('utf-8')
        jsondata = json.loads(result)

        for info in jsondata["showapi_res_body"]["pagebean"]["contentlist"]:
            speed = float(info['speed'])
            if speed < 3:
                ip = str(info['ip'])
                port = str(info['port'])
                proxy.append(ip + ":" + port)

    except Exception as e:
        print(e)

    return proxy


def ip_available(proxy):
    server = proxy
    
    try:
        opener = request.build_opener(request.ProxyHandler({'http':server}))
        request.install_opener(opener)

        url = "http://www.baidu.com"
        response = request.urlopen(url, timeout=3)
        code = response.getcode()

        return code == 200
    except Exception as e:
        pass


# meet 20 available ip
if __name__ == '__main__':
    proxy_pool = set()

    # old_proxy
    old_proxy = []
    file = open('../proxy_ip')
    for proxy in file.readlines():
        old_proxy.append(proxy)
    file.close()

    os.system("echo \033[32m[" + "================old================" + "]\033[0m")

    for proxy in old_proxy:
        proxy = proxy.split('\n')[0]
        if ip_available("http://" + proxy):
            proxy_pool.add(proxy)
            os.system("echo \033[32m[" + proxy + " is available!" + "]\033[0m")
        else:
            print(proxy + " is not available!")

    os.system("echo \033[32m[" + "================end================" + "]\033[0m")

    os.system("echo \033[32m[" + "================new================" + "]\033[0m")

    number = 0;
    while len(proxy_pool) < 20:
        number += 1;
        if number > 10:
            break
        # new_proxy
        new_proxy = get_proxy()
        for proxy in new_proxy:
            if len(proxy_pool) >= 20:
                break
            if ip_available("http://" + proxy):
                proxy_pool.add(proxy)
                os.system("echo \033[32m[" + proxy + " is available!" + "]\033[0m")
            else:
                print(proxy + " is not available!")

        time.sleep(10)

    os.system("echo \033[32m[" + "================end================" + "]\033[0m")

    os.system("rm ../proxy_ip")
    os.system("touch ../proxy_ip")
    file = open('../proxy_ip', 'w')
    for proxy in proxy_pool:
        file.write(proxy+'\n')
    file.close()
    
    os.system("echo \033[32m[" + "proxy task complete!" + "]\033[0m")














