.PHONY: module clean

SRC = $(shell readlink -f ../..)

lua_exe_path = $(shell realpath $$(which lua)) 

module:
	echo "/lua: ${lua_exe_path}" > usr.manifest
	echo '/hello.lua: $${MODULE_DIR}/hello.lua' >> usr.manifest
	$(SRC)/scripts/manifest_from_host.sh $(lua_exe_path) >> usr.manifest

clean:
	rm -rf usr.manifest
