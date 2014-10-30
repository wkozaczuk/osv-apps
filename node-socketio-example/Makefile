.PHONY: module test browser_test clean
module: ROOTFS

ROOTFS: ROOTFS/chat-example

ROOTFS/chat-example:
	mkdir -p ROOTFS
	git clone https://github.com/guille/chat-example.git --depth 1 ROOTFS/chat-example
	cd ROOTFS/chat-example && npm install
	patch -p0 < remove-isvalidutf8.patch

test:
	python test.py

browser_test:
	Xvfb :1 -screen 0 1024x768x24 &
	env DISPLAY=:1 python browser_test.py
	killall Xvfb

clean:
	rm -rf ROOTFS
