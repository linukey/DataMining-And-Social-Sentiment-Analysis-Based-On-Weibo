#!/bin/bash

# create redis server
docker image pull redis
echo "\033[32m[create redis server end!]\033[0m"

# create scrapy-redis
docker image pull linukey/scrapy-redis
echo "\033[32m[create scrapy-redis end!]\033[0m"

# create weibo_client
docker build -t weibo weibo_client
echo "\033[32m[create weibo_client end!]\033[0m"

# if you want more client, to create weibo_client1 weibo_client2 etc...

echo
echo
echo "\033[32m[create all end, to exit!]\033[0m"
echo
echo

docker image ls
