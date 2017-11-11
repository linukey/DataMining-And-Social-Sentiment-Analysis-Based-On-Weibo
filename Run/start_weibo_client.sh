#!/bin/bash

rm weibo_client.log 2>/dev/null
nohup docker container run --link rs --expose 6379 --name weibo_client weibo sh run_crawl.sh >weibo_client.log 2>&1 &
echo "\033[32m[run weibo_client end!]\033[0m"
