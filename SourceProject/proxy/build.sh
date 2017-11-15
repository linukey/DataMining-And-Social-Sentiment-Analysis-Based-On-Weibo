#!/bin/bash

echo "\033[33m[========================clean pre build============================]\033[0m"
sh ./clean.sh
echo "\033[33m[===================================================================]\033[0m"
echo
echo
echo "\033[33m[========================building proxymanager======================]\033[0m"
make -C proxymanager/cpp
echo "\033[33m[===================================================================]\033[0m"
echo
echo
echo "\033[33m[========================building webserver=========================]\033[0m"
make -C webserver
cp webserver/run_server .
echo "\033[33m[===================================================================]\033[0m"
echo
echo
echo "\033[33m[add flow config to your $HOME/.bashrc]\033[0m"
echo "\033[32m[===================================================================]\033[0m"
echo "export LD_LIBRARY_PATH=`pwd`/proxymanager/cpp:\$LD_LIBRARY_PATH >>$HOME/.bashrc"
echo "export LIBRARY_PATH=`pwd`/proxymanager/cpp:\$LIBRARY_PATH >>$HOME/.bashrc"
echo "\033[32m[===================================================================]\033[0m"
