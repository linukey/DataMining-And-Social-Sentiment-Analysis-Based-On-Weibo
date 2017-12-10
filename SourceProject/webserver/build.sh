#!/bin/bash

sh ./clean.sh
echo
echo
echo "\033[33m[========================building proxymanager======================]\033[0m"
make -C ../proxymanager/cpp
echo "\033[33m[===================================================================]\033[0m"
echo
echo
echo "\033[33m[========================building spidermanager======================]\033[0m"
make -C ../spidermanager
echo "\033[33m[===================================================================]\033[0m"
echo
echo
echo "\033[33m[========================building webserver=========================]\033[0m"
make
echo "\033[33m[===================================================================]\033[0m"
echo
echo
echo "\033[33m[add flow config to your $HOME/.bashrc]\033[0m"
echo "\033[32m[===================================================================]\033[0m"
echo "export LD_LIBRARY_PATH=`pwd`/proxymanager/cpp:\$LD_LIBRARY_PATH >>$HOME/.bashrc"
echo "export LIBRARY_PATH=`pwd`/proxymanager/cpp:\$LIBRARY_PATH >>$HOME/.bashrc"
echo "\033[32m[===================================================================]\033[0m"
