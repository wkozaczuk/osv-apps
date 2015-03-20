.PHONY: module

VERSION := 0.2.3-Helium-SR3
URL := https://nexus.opendaylight.org/content/repositories/opendaylight.release/org/opendaylight/integration/distribution-karaf/$(VERSION)/distribution-karaf-$(VERSION).zip

module: ROOTFS

distribution-karaf-$(VERSION).zip:
	wget $(URL)

opendaylight: distribution-karaf-$(VERSION).zip
	unzip -x distribution-karaf-$(VERSION).zip

ROOTFS/opendaylight: opendaylight
	mkdir -p ROOTFS/opendaylight
	cp -a distribution-karaf-$(VERSION)/bin distribution-karaf-$(VERSION)/configuration distribution-karaf-$(VERSION)/data distribution-karaf-$(VERSION)/deploy distribution-karaf-$(VERSION)/etc distribution-karaf-$(VERSION)/externalapps distribution-karaf-$(VERSION)/lib distribution-karaf-$(VERSION)/version.properties distribution-karaf-$(VERSION)/system ROOTFS/opendaylight

ROOTFS: ROOTFS/opendaylight

clean:
	rm -rf distribution-karaf-$(VERSION) ROOTFS
