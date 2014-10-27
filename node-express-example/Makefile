.PHONY: module test clean

module: ROOTFS

ROOTFS: ROOTFS/express

ROOTFS/express:
	mkdir -p ROOTFS
	git clone git://github.com/strongloop/express.git --depth 1 ROOTFS/express
	cd ROOTFS/express && npm install
test:
	python test.py
clean:
	rm -rf ROOTFS npm-debug.log
