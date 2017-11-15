#!/bin/bash

make -C proxymanager/cpp
make -C webserver

cp webserver/run_server .

echo export LD_LIBRARY_PATH=`pwd`/proxymanager/cpp:\$LD_LIBRARY_PATH >>$HOME/.bashrc
echo export LIBRARY_PATH=`pwd`/proxymanager/cpp:\$LIBRARY_PATH >>$HOME/.bashrc

source $HOME/.bashrc
