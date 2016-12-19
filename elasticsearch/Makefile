VERSION:=2.4.2
NAME:=elasticsearch
DIR:=$(NAME)-$(VERSION)
TARBALL:=$(DIR).tar.gz
URL:=https://download.elastic.co/elasticsearch/release/org/elasticsearch/distribution/tar/elasticsearch/$(VERSION)/$(TARBALL)

module: ROOTFS usr.manifest

$(TARBALL):
	wget $(URL)

ROOTFS/$(NAME): $(TARBALL)
	tar xvf $(TARBALL)
	mkdir -p ROOTFS
	mv $(DIR) ROOTFS/$(NAME)
	touch ROOTFS/$(NAME)
	find ./assets/config -type f -exec cp {} ROOTFS/$(NAME)/config/. \;

usr.manifest:
	echo "/$(NAME)/**: \$${MODULE_DIR}/ROOTFS/$(NAME)/**" > usr.manifest

clean:
	rm -rf ROOTFS $(DIR)
	rm -f usr.manifest $(TARBALL)

ROOTFS: ROOTFS/$(NAME)
