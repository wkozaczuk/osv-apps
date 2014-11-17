
LIB_NODE = node-$(NODE_VERSION)/out/Release/lib.target/libnode.so

libnode.so: $(LIB_NODE)
	cp $^ $@

$(LIB_NODE):
	cd node-$(NODE_VERSION); ./configure
	$(MAKE) -C node-$(NODE_VERSION)

# Support for OSv's combined kernel+module build system ('make modules=node'
# and 'make clean')
VERSION=0.10.33
module:
	if test ! -d node-$(VERSION); then ./GET $(VERSION); $(MAKE) NODE_VERSION=$(VERSION); fi
	echo '/libnode.so: $${MODULE_DIR}/libnode.so' > usr.manifest
	: > bootfs.manifest
clean:
	rm -rf node-$(VERSION) usr.manifest bootfs.manifest libnode.so
