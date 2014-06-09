.PHONY: module

VERSION := 0.1.1
URL := https://nexus.opendaylight.org/content/repositories/opendaylight.release/org/opendaylight/integration/distributions-base/$(VERSION)/distributions-base-$(VERSION)-osgipackage.zip

module: ROOTFS

distributions-base-${VERSION}-osgipackage.zip:
	wget $(URL)

opendaylight: distributions-base-${VERSION}-osgipackage.zip
	unzip -x distributions-base-${VERSION}-osgipackage.zip

ROOTFS/opendaylight: opendaylight
	mkdir -p ROOTFS/opendaylight
	cp -a opendaylight/configuration opendaylight/plugins opendaylight/version.properties opendaylight/lib ROOTFS/opendaylight

ROOTFS: ROOTFS/opendaylight

clean:
	rm -rf opendaylight ROOTFS *.zip
