.PHONY: module

VERSION := 10.10.2.0

module: ROOTFS

db-derby-$(VERSION)-bin.tar.gz:
	wget http://archive.apache.org/dist/db/derby/db-derby-10.10.2.0/db-derby-10.10.2.0-bin.tar.gz

ROOTFS/db-derby: db-derby-$(VERSION)-bin.tar.gz
	mkdir -p ROOTFS/db-derby
	tar xvf db-derby-$(VERSION)-bin.tar.gz
	cp -a db-derby-$(VERSION)-bin/lib ROOTFS/db-derby

ROOTFS/db-derby/security.policy:
	cp security.policy ROOTFS/db-derby

ROOTFS: ROOTFS/db-derby ROOTFS/db-derby/security.policy

clean:
	rm -rf ROOTFS db-derby-*
