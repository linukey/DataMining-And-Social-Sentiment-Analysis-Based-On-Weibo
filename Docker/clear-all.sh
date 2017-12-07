#!/bin/bash

docker container stop webserver
docker container stop redis
docker container stop spider-one
docker container stop spider-two

docker container rm webserver
docker container rm redis
docker container rm spider-one
docker container rm spider-two
