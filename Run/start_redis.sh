#!/bin/bash

docker container run --expose 6379 --name rs -d redis
echo "\033[32m[run redis server end!]\033[0m"
