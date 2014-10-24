# Support for OSv's combined kernel+module build system
# ('make modules=node-demo' and 'make clean')
module: ROOTFS

ROOTFS: ROOTFS/express

ROOTFS/express:
	mkdir -p ROOTFS
	git clone git://github.com/strongloop/express.git --depth 1 ROOTFS/express
	cd ROOTFS/express && npm install
clean:
	rm -rf ROOTFS npm-debug.log
