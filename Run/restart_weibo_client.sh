#!/bin/bash

rm weibo_client.log 2>/dev/null
docker container start weibo_client >weibo_client.log 2>&1
echo "\033[32m[run weibo_client end!]\033[0m"
