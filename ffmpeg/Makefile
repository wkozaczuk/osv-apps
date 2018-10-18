#
# Copyright (C) 2018 Waldek Kozaczuk
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

SRCDIR=upstream
VERSION=4.0.2
DOWNLOAD_URL=https://www.ffmpeg.org/releases/
TARBALL=ffmpeg-${VERSION}.tar.xz
module: ROOTFS/ffmpeg.so

${SRCDIR}/ffmpeg-${VERSION}:
	mkdir -p upstream
	wget -c -O upstream/${TARBALL} ${DOWNLOAD_URL}/${TARBALL}
	cd upstream && tar xf ${TARBALL}

${SRCDIR}/ffmpeg-${VERSION}/ffmpeg: ${SRCDIR}/ffmpeg-${VERSION}
	cd ${SRCDIR}/ffmpeg-${VERSION} && ./configure --disable-static --enable-shared --disable-ffplay --disable-ffprobe
	cd ${SRCDIR}/ffmpeg-${VERSION} && make
	cd ${SRCDIR}/ffmpeg-${VERSION} && rm ffmpeg ffmpeg_g fftools/*.o fftools/*.d
	patch ${SRCDIR}/ffmpeg-${VERSION}/fftools/Makefile fftools_makefile.patch
	cd ${SRCDIR}/ffmpeg-${VERSION} && make #Force rebuild ffmpeg executable as shared object

ROOTFS/ffmpeg.so: ${SRCDIR}/ffmpeg-${VERSION}/ffmpeg
	mkdir -p ROOTFS
	cp ${SRCDIR}/ffmpeg-${VERSION}/ffmpeg ROOTFS/ffmpeg.so
	find ${SRCDIR}/ffmpeg-${VERSION} -regex '.*\.so\.[0-9]+' | xargs -I {} cp {} ROOTFS/
	strip ROOTFS/*

clean:
	rm -rf upstream ROOTFS
