src = $(shell readlink -f ../..)
app-dir = $(src)/apps/ratpack-example

all: module
module: ratpack-example

module: eugenp-examples/.git
	cd $(app-dir)/eugenp-examples/ratpack && mvn -Dgib.enabled=false package
	echo "/ratpack.jar : $(app-dir)/eugenp-examples/ratpack/target/ratpack.jar" > $(app-dir)/usr.manifest

.PHONY: ratpack-example

eugenp-examples/.git:
	cd $(app-dir) && git clone --depth 1 https://github.com/eugenp/tutorials.git eugenp-examples

clean:
	cd $(app-dir) && rm -rf eugenp-examples && rm -f usr.manifest
