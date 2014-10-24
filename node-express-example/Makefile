# Support for OSv's combined kernel+module build system
# ('make modules=node-demo' and 'make clean')
module:
	if test ! -d express; \
		then git clone git://github.com/strongloop/express.git --depth 1 express; \
		cd express; npm install; \
		fi
	echo '/express/**: $${MODULE_DIR}/express/**' > usr.manifest
	: > bootfs.manifest
clean:
	rm -rf usr.manifest bootfs.manifest express npm-debug.log
