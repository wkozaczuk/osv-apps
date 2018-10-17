src = $(shell readlink -f ../..)
app-dir = $(src)/apps/ratpack-example

all: module
module: ratpack-example

module: $(app-dir)/upstream/eugenp-examples/.git
	cd $(app-dir)/upstream/eugenp-examples/ratpack && mvn -Dgib.enabled=false package
	mkdir -p $(app-dir)/ROOTFS && cd $(app-dir)/ROOTFS && jar xf ../upstream/eugenp-examples/ratpack/target/ratpack.jar
	echo "/ratpack-app/* : $(app-dir)/ROOTFS/*" > $(app-dir)/usr.manifest

.PHONY: ratpack-example

$(app-dir)/upstream/eugenp-examples/.git:
	mkdir -p $(app-dir)/upstream
	cd $(app-dir)/upstream && git clone --depth 1 https://github.com/eugenp/tutorials.git
	patch $(app-dir)/upstream/ratpack/pom.xml pom.patch

clean:
	cd $(app-dir) && rm -rf upstream ROOTFS usr.manifest
