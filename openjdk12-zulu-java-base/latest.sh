#!/bin/bash
DOWNLOAD_URL_SUFFIX=`wget -c -qO- https://cdn.azul.com/zulu/bin/ | grep -o '<a href=['"'"'"][^"'"'"']*['"'"'"]' | grep "jdk12.*linux.*64.tar.gz\"" | grep -o "zulu.*tar.gz" | tail -n 1`
DOWNLOAD_URL="https://cdn.azul.com/zulu/bin/$DOWNLOAD_URL_SUFFIX"
VERSION=`echo $DOWNLOAD_URL | grep -o "zulu12.*linux_x64"`

if [ "$1" = "version" ]; then
echo $VERSION
else
echo $DOWNLOAD_URL
fi
