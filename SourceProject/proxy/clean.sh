#!/bin/bash

echo "\033[33m[=============================clean=================================]\033[0m"
make -C proxymanager/cpp clean
make -C webserver clean
rm run_server
echo must to delete the ld_config in the $HOME/.bashrc by yourself
echo "\033[33m[===================================================================]\033[0m"
