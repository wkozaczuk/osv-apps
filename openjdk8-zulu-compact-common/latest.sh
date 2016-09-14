#!/bin/bash

wget -qO- http://www.azul.com/downloads/zulu/zulu-linux/ | grep "jdk8.*linux.*64.tar.gz" | grep -o "http:.*tar.gz" | head -1
