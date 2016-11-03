#
# Copyright (C) 2013 Cloudius Systems, Ltd.
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

.PHONY: module clean

jvm_dir=install/usr/lib/jvm

java_version=$(shell ./latest.sh)
java_dir=http://www.java.net/download/java/jdk9/archive/$(java_version)/binaries/
java_fullname=jdk-9-ea+$(java_version)_linux-x64_bin.tar.gz

jre_name=jdk-9-ea-$(java_version)-java-base
linked_jre_dir=usr/lib/jvm/$(jre_name)

SRC = $(shell readlink -f ../..)

module:
	cd $(SRC)/java && mvn package -q -DskipTests=true
	mkdir -p upstream
	wget -c -O upstream/$(java_fullname) $(java_dir)$(java_fullname)
	rm -rf install
	mkdir -p install/$(linked_jre_dir)
	cd install && tar xfz ../upstream/$(java_fullname)
	cd install && jdk-9/bin/jlink --module-path jdk-9/jmods --add-modules java.base --output $(linked_jre_dir)/jre  --strip-debug --compress=2
	rm -rf install/jdk-9
	ln -sf $(jre_name) $(jvm_dir)/java
	rm -rf $(jvm_dir)/java/jre/lib/security/cacerts
	rm -rf $(jvm_dir)/java/jre/lib/audio/*
	ln -s /etc/pki/java/cacerts install/usr/lib/jvm/java/jre/lib/security/

clean:
	rm -rf upstream install
	cd $(SRC)/java && mvn clean -q
	-rm -f dependency-reduced-pom.xml
