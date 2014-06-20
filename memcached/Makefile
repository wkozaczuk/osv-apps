.PHONY: module
module: memcached
	echo '/memcached: $${MODULE_DIR}/memcached' > usr.manifest
	ldd memcached | grep libevent | \
		sed 's/ *[^ ] *\(.*\) => \(.*\) .*/\/\1: \2/' \
		>> usr.manifest
	: > bootfs.manifest

src:
	./GET

sources := assoc.c cache.c daemon.c hash.c items.c memcached.c slabs.c \
	stats.c thread.c util.c

sources := $(addprefix src/, $(sources))

$(sources): src

CFLAGS = -std=gnu99 -fPIC -DHAVE_CONFIG_H

memcached: $(sources)
	$(CC) -pie -o $@ $(CFLAGS) $(LDFLAGS) $(sources) -levent -lpthread

clean:
	rm -rf upstream src
	rm -f bootfs.manifest usr.manifest module.pyc memcached
