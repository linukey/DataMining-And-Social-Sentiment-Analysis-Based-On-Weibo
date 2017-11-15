#!/bin/bash

make -C proxymanager/cpp clean
make -C webserver clean
rm run_server

echo must to delete the ld_config in the $HOME/.bashrc by yourself
