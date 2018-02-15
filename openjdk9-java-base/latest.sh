#!/bin/bash
wget -c -qO- http://jdk.java.net/9/ | grep "https://download.java.net/java/GA/jdk9.*linux-x64_bin.tar.gz\"" | grep -o "openjdk-.*linux" | grep -o '9\.[0-9]\+\.[0-9]\+'
