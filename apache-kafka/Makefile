SCALA:=2.10
VERSION:=0.8.2.1
NAME:=kafka
DIR:=kafka_$(SCALA)-$(VERSION)
TARBALL:=$(DIR).tgz
URL:=http://mirror.ventraip.net.au/apache/$(NAME)/$(VERSION)/$(TARBALL)


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
