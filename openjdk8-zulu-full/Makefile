#
# Copyright (C) 2017 Waldemar Kozaczuk
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

jvm_dir=install/usr/lib/jvm

java8_jdk_tarball_url = $(shell ./latest.sh)

java8_name = $(shell echo $(java8_jdk_tarball_url) | grep -o zulu8.*x64)

SRC = $(shell readlink -f ../..)

module:
	mkdir -p upstream
	wget -c -O upstream/openjdk8.tar.gz $(java8_jdk_tarball_url)
	rm -rf install
	mkdir -p $(jvm_dir)/java
	cd install && tar xfz ../upstream/openjdk8.tar.gz
	mv install/$(java8_name)/jre $(jvm_dir)/java/jre
	rm -rf install/$(java8_name)
	rm -rf $(jvm_dir)/java/jre/bin
	rm -rf $(jvm_dir)/java/jre/lib/security/cacerts
	rm -rf $(jvm_dir)/java/jre/lib/audio/*
	ln -s /etc/pki/java/cacerts install/usr/lib/jvm/java/jre/lib/security/

clean:
	rm -rf upstream install
