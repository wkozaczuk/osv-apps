#!/bin/bash
jvm_dir=install/usr/lib/jvm

java_dir=https://s3.amazonaws.com/org.waldiko-openjdk8/
java_fullname=java-1.8.0-openjdk-1.8.0.92.b14.x86_64-compact1.tar.gz

mkdir upstream
wget -c -O upstream/$java_fullname $java_dir$java_fullname
rm -rf install
mkdir -p install/usr/lib/jvm/java/jre
tar xfz upstream/$java_fullname -C install/
ln -sf install/j2re-compact1-image $jvm_dir/java/jre
#rm -rf $(jvm_dir)/java/jre/lib/security/cacerts
#rm -rf $(jvm_dir)/java/jre/lib/audio/*
#cp $(SRC)/java/runjava/target/runjava.jar install/usr/lib/jvm/java/jre/lib/ext/
#ln -s /etc/pki/java/cacerts install/usr/lib/jvm/java/jre/lib/security/
