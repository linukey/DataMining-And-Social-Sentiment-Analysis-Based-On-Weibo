#!/usr/bin/python3.5

from urllib import request, parse
import json
import os
import time

def get_proxy():
	# this is my appid and sign, my ip has been added to the server whitelist
	# so, i can use this appid and sign
	# if you want to get your, to this url: https://www.showapi.com/api/lookPoint/22/1#price
    showapi_appid = "49824"
    showapi_sign = "6e1680fb4ab2468aac8e2c138b7b108a"

    url = "http://route.showapi.com/22-1"
    send_data = parse.urlencode([
        ('showapi_appid', showapi_appid),
        ('showapi_sign', showapi_sign)
    ])

    proxy = []
    req = request.Request(url)
    try:
        response = request.urlopen(req, data=send_data.encode('utf-8'), timeout=10)
        result = response.read().decode('utf-8')
        jsondata = json.loads(result)

        for info in jsondata["showapi_res_body"]["pagebean"]["contentlist"]:
            speed = float(info['speed'])
            if speed < 3:
                ip = str(info['ip'])
                port = str(info['port'])
                proxy.append(ip + ":" + port)
    
    except Exception as e:
        #print(e)
        pass
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
def update_proxy_ip(proxy_num, proxy_path):
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
            #os.system("echo \033[32m[" + proxy + " is available!" + "]\033[0m")
        else:
            #print(proxy + " is not available!")
            pass

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
                #os.system("echo \033[32m[" + proxy + " is available!" + "]\033[0m")
            else:
                #print(proxy + " is not available!")
                pass

        time.sleep(10)

    # write the proxy_result into proxy_ip
    file = open(proxy_path, 'w')
    for proxy in proxy_pool:
        file.write(proxy+'\n')
    file.close()
    print("\n\n")
    os.system("echo \033[32m[" + "update proxy success! respect proxy_cnt:" + str(proxy_num) + " actual proxy_cnt:" + str(len(proxy_pool)) + "]\033[0m")

    return len(proxy_pool)
