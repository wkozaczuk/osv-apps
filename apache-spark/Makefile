HADOOP_VERSION:=2.4
VERSION:=1.3.0
NAME:=spark
DIR:=$(NAME)-$(VERSION)-bin-hadoop$(HADOOP_VERSION)
TARBALL:=$(DIR).tgz
URL:=http://d3kbcqa49mib13.cloudfront.net/$(TARBALL)

.PHONY: module

module: ROOTFS

$(TARBALL):
	wget $(URL)

$(NAME): $(TARBALL)
	tar xvf $(TARBALL)

ROOTFS/$(NAME): $(NAME)
	mkdir -p ROOTFS
	mv $(DIR) ROOTFS/$(NAME)
	find ./assets/conf -type f -exec cp {} ROOTFS/$(NAME)/conf/. \;

manifest:
	echo "/$(NAME)/**: \$${MODULE_DIR}/ROOTFS/$(NAME)/**" > usr.manifest

clean:
	rm -rf ROOTFS usr.manifest

ROOTFS: clean manifest ROOTFS/$(NAME)
