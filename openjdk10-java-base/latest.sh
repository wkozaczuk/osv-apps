#!/bin/bash
DOWNLOAD_URL=`wget -c -qO- http://jdk.java.net/10/ | grep -o "https://download.java.net/java/GA/jdk10.*linux-x64_bin.tar.gz\"" | grep -o "https.*tar.gz"`
VERSION=`echo $DOWNLOAD_URL | grep -o "openjdk-.*linux" | grep -o '10\.[0-9]\+\.[0-9]\+'`

if [ "$1" = "version" ]; then
echo $VERSION
else
echo $DOWNLOAD_URL
fi
