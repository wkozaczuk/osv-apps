#!/bin/bash
DOWNLOAD_URL=`wget -c -qO- http://www.azul.com/downloads/zulu/zulu-linux | grep "jdk9.*linux.*64.tar.gz\"" | grep -o "https:.*tar.gz" | head -n 1`
VERSION=`echo $DOWNLOAD_URL | grep -o "zulu9.*linux_x64"`

if [ "$1" = "version" ]; then
echo $VERSION
else
echo $DOWNLOAD_URL
fi
