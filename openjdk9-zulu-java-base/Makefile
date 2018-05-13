#
# Copyright (C) 2013 Cloudius Systems, Ltd.
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

.PHONY: module clean

jvm_dir=install/usr/lib/jvm

download_url=$(shell ./latest.sh)
java_version=$(shell ./latest.sh version)
java_fullname=$(java_version)_bin.tar.gz

jre_name=jdk-$(java_version)-java-base
linked_jre_dir=usr/lib/jvm/$(jre_name)

SRC = $(shell readlink -f ../..)

module:
	mkdir -p upstream
	wget -c -O upstream/$(java_fullname) $(download_url)
	cd upstream && tar xfz $(java_fullname)
	rm -rf install && mkdir install
	cd install && ../upstream/$(java_version)/bin/jlink --module-path ../upstream/$(java_version)/jmods --add-modules java.base --output $(linked_jre_dir) --strip-debug --compress=2
	cd install && rm -rf $(linked_jre_dir)/bin
	ln -sf $(jre_name) $(jvm_dir)/java
	rm -rf $(jvm_dir)/java/lib/security/cacerts
	ln -s /etc/pki/java/cacerts install/usr/lib/jvm/java/lib/security/

clean:
	rm -rf upstream install
