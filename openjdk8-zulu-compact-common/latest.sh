#!/bin/bash

wget -c -qO- http://www.azul.com/downloads/zulu/zulu-linux | grep -o '<a href=['"'"'"][^"'"'"']*['"'"'"]' | grep "jdk8.*linux.*64.tar.gz\"" | cut -d'"' -f2 | head -1
