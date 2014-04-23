#
# Copyright (C) 2013 Cloudius Systems, Ltd.
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

.PHONEY: module get

jvm.dir = install/usr/lib/jvm

module: get
	rpm2cpio upstream/jdk8.rpm | (cd install && cpio -id)
	ln -sf jre-1.8.0-openjdk.x86_64 $(jvm.dir)/jre
get:
	./GET
