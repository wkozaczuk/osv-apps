VERSION=2.0.9
current_name=apache-cassandra-$(VERSION)
dir=upstream/$(current_name)
tarball_name=apache-cassandra-$(VERSION)-bin.tar.gz
tarball=upstream/$(tarball_name)
jna_version=3.2.7
jna=upstream/jna-$(jna_version).jar

.PHONY: module
module: $(dir)
	rm -rf ROOTFS
	mkdir -p ROOTFS/usr/cassandra/lib
	mkdir -p ROOTFS/usr/cassandra/conf
	cp --reflink=auto -r $(dir)/lib ROOTFS/usr/cassandra
	cp --reflink=auto -r $(dir)/conf ROOTFS/usr/cassandra
	cp --reflink=auto $(jna) ROOTFS/usr/cassandra/lib
	ln -sfn $(current_name) upstream/current

$(dir): $(tarball) $(jna) upstream
	cd upstream && tar zxvf $(tarball_name)
	cd $(dir) && patch -p1 < ../../cassandra-osv.patch
	touch $@

upstream:
	mkdir -p $@

$(tarball): upstream
	cd upstream && wget -nc http://archive.apache.org/dist/cassandra/$(VERSION)/$(tarball_name)
	touch $@

$(jna): upstream
	cd upstream && wget -nc http://download.java.net/maven/2/net/java/dev/jna/jna/$(jna_version)/jna-$(jna_version).jar
	touch $@

clean:
	rm -rf ROOTFS upstream
