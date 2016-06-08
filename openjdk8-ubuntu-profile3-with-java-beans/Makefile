#
# Copyright (C) 2013 Cloudius Systems, Ltd.
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

.PHONY: module clean

jvm_dir=install/usr/lib/jvm

java_dir=https://s3.amazonaws.com/org.waldiko-openjdk8/
java_fullname=java-1.8.0-openjdk-1.8.0.92.b14.x86_64-compact3-with-java-beans.tar.gz

SRC = $(shell readlink -f ../..)

module:
	cd $(SRC)/java && mvn package -q -DskipTests=true
	mkdir -p upstream
	wget -c -O upstream/$(java_fullname) $(java_dir)$(java_fullname)
	rm -rf install
	mkdir -p install/usr/lib/jvm/j2re-compact3-image-with-java-beans
	tar xfz upstream/$(java_fullname) -C install/
	mv install/j2re-compact3-image-with-java-beans $(jvm_dir)/j2re-compact3-image-with-java-beans/jre
	ln -sf j2re-compact3-image-with-java-beans install/usr/lib/jvm/java
	rm -rf $(jvm_dir)/java/jre/lib/security/cacerts
	rm -rf $(jvm_dir)/java/jre/lib/audio/*
	cp $(SRC)/java/runjava/target/runjava.jar install/usr/lib/jvm/java/jre/lib/ext/
	ln -s /etc/pki/java/cacerts install/usr/lib/jvm/java/jre/lib/security/

clean:
	rm -rf upstream install
	cd $(SRC)/java && mvn clean -q
	-rm -f dependency-reduced-pom.xml
