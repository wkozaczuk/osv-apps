#!/bin/bash

if [ `memaslap -h | wc -l` -gt 1 ]  
    then  
       echo "already installed"
       exit 0
fi

FILE=https://launchpad.net/libmemcached/1.0/1.0.18/+download/libmemcached-1.0.18.tar.gz

wget $FILE
tar xvf  $FILE

mv libmemcached* libmemcached
cd libmemcached
./configure
make

