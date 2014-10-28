.PHONY: module test clean
module: ROOTFS

ROOTFS: ROOTFS/chat-example

ROOTFS/chat-example:
	mkdir -p ROOTFS
	git clone https://github.com/guille/chat-example.git --depth 1 ROOTFS/chat-example
	cd ROOTFS/chat-example && npm install
	patch -p0 < remove-isvalidutf8.patch

test:
	python test.py

clean:
	rm -rf ROOTFS
