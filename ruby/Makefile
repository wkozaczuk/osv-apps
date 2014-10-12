.PHONY: module
module: ruby.so usr.manifest

CFLAGS=-fPIC -Wall -shared

SSL_VER=1.0.1i
OPENSSL=upstream/openssl-${SSL_VER}/apps/openssl

RUBY_LDFLAGS=-lm -lcrypt -ldl -lpthread -lruby
LIBS=-Lupstream/ruby
INCS=-Iupstream/ruby/include -Iupstream/ruby/.ext/include/x86_64-linux/

LIBRUBY=upstream/ruby/libruby.so

OBSTACK_OBJS=upstream/obstack-1.2/.libs/obstack.o upstream/obstack-1.2/.libs/obstack_printf.o upstream/obstack-1.2/.libs/obstack_vprintf.o
LIBOBSTACK_A=upstream/obstack-1.2/.libs/libobstack.a

EXT_OPENSSL=upstream/ruby/ext/openssl/Makefile.orig
EXT_DIGEST_MD5=upstream/ruby/ext/digest/md5/Makefile.orig
EXT_DIGEST_RMD160=upstream/ruby/ext/digest/rmd160/Makefile.orig
EXT_DIGEST_SHA1=upstream/ruby/ext/digest/sha1/Makefile.orig
EXT_DIGEST_SHA2=upstream/ruby/ext/digest/sha2/Makefile.orig

upstream/ruby:
	mkdir -p upstream
	cd upstream && git clone --depth 1 -b v2_1_2 https://github.com/ruby/ruby.git && cd ruby && patch -p1 < ../../no-use-sleepy-thread-timer-ruby.patch
	cd upstream/ruby && autoconf
	cd upstream/ruby && ./configure --libdir=/usr/lib --enable-pic --enable-shared --disable-install-doc --disable-install-rdoc

upstream/obstack-1.2.tar.bz2:
	mkdir -p upstream
	cd upstream && wget -O obstack-1.2.tar.bz2 "http://sourceforge.jp/frs/g_redir.php?m=jaist&f=%2Flibfirm%2Fobstack%2F1.2%2Fobstack-1.2.tar.bz2"
	cd upstream && tar xvf obstack-1.2.tar.bz2
	cd upstream/obstack-1.2/ && patch -p1 < ../../obstack_vprintf.patch
	cd upstream/obstack-1.2/ && ./configure

upstream/openssl-${SSL_VER}.tar.gz:
	mkdir -p upstream
	cd upstream && wget -O openssl-${SSL_VER}.tar.gz "http://www.openssl.org/source/openssl-${SSL_VER}.tar.gz"
	cd upstream && tar xvf openssl-${SSL_VER}.tar.gz
	cd upstream/openssl-${SSL_VER} && ./config && mv Makefile Makefile.orig && sed -e "s/CFLAG= /CFLAG= -fPIC /" Makefile.orig > Makefile

upstream/bundler:
	mkdir -p upstream
	cd upstream && git clone --depth 1 https://github.com/bundler/bundler.git

upstream/cert.pem:
	mkdir -p upstream
	cd upstream && wget -O cert.pem "http://curl.haxx.se/ca/cacert.pem"

${OPENSSL}: upstream/openssl-${SSL_VER}.tar.gz
	cd upstream/openssl-${SSL_VER} && make MAKEFLAGS=

${LIBOBSTACK_A}: upstream/obstack-1.2.tar.bz2
	cd upstream/obstack-1.2/ && make

${LIBRUBY}: upstream/ruby
	cd upstream/ruby && make

${EXT_OPENSSL}: ${LIBRUBY} ${OPENSSL}
	cd upstream/ruby/ext/openssl && mv Makefile Makefile.orig
	cd upstream/ruby/ext/openssl && sed -e "s#-lssl#../../../openssl-${SSL_VER}/libssl.a#" Makefile.orig|sed -e "s#-lcrypto#../../../openssl-${SSL_VER}/libcrypto.a#" > Makefile
	cd upstream/ruby/ext/openssl && make
${EXT_DIGEST_MD5}: ${LIBRUBY} ${OPENSSL}
	cd upstream/ruby/ext/digest/md5 && mv Makefile Makefile.orig
	cd upstream/ruby/ext/digest/md5 && sed -e "s#-lssl#../../../../openssl-${SSL_VER}/libssl.a#" Makefile.orig|sed -e "s#-lcrypto#../../../../openssl-${SSL_VER}/libcrypto.a#" > Makefile
	cd upstream/ruby/ext/digest/md5 && make
${EXT_DIGEST_RMD160}: ${LIBRUBY} ${OPENSSL}
	cd upstream/ruby/ext/digest/rmd160 && mv Makefile Makefile.orig
	cd upstream/ruby/ext/digest/rmd160 && sed -e "s#-lssl#../../../../openssl-${SSL_VER}/libssl.a#" Makefile.orig|sed -e "s#-lcrypto#../../../../openssl-${SSL_VER}/libcrypto.a#" > Makefile
	cd upstream/ruby/ext/digest/rmd160 && make
${EXT_DIGEST_SHA1}: ${LIBRUBY} ${OPENSSL}
	cd upstream/ruby/ext/digest/sha1 && mv Makefile Makefile.orig
	cd upstream/ruby/ext/digest/sha1 && sed -e "s#-lssl#../../../../openssl-${SSL_VER}/libssl.a#" Makefile.orig|sed -e "s#-lcrypto#../../../../openssl-${SSL_VER}/libcrypto.a#" > Makefile
	cd upstream/ruby/ext/digest/sha1 && make
${EXT_DIGEST_SHA2}: ${LIBRUBY} ${OPENSSL}
	cd upstream/ruby/ext/digest/sha2 && mv Makefile Makefile.orig
	cd upstream/ruby/ext/digest/sha2 && sed -e "s#-lssl#../../../../openssl-${SSL_VER}/libssl.a#" Makefile.orig|sed -e "s#-lcrypto#../../../../openssl-${SSL_VER}/libcrypto.a#" > Makefile
	cd upstream/ruby/ext/digest/sha2 && make

ruby.so: ${LIBOBSTACK_A} ${LIBRUBY}
	cc ${CFLAGS} -c ${INCS} upstream/ruby/main.c 
	cc ${CFLAGS} -o ruby.so ${LIBS} ${RUBY_LDFLAGS} ./main.o ${OBSTACK_OBJS}

usr.manifest: ruby.so upstream/bundler upstream/cert.pem ${OPENSSL} ${EXT_OPENSSL} ${EXT_DIGEST_MD5} ${EXT_DIGEST_RMD160} ${EXT_DIGEST_SHA1} ${EXT_DIGEST_SHA2}
	cp -a ./upstream/ruby/.ext/common/* ./upstream/ruby/lib/
	cp -a ./upstream/bundler/lib/* ./upstream/ruby/lib/
	echo '/ruby.so: $${MODULE_DIR}/ruby.so' > usr.manifest
	echo '/**: $${MODULE_DIR}/upstream/ruby/bin/**' >> usr.manifest
	echo '/libruby.so.2.1: $${MODULE_DIR}/upstream/ruby/libruby.so' >> usr.manifest
	echo '/usr/lib/ruby/2.1.0/**: $${MODULE_DIR}/upstream/ruby/lib/**' >> usr.manifest
	echo '/usr/lib/ruby/2.1.0/x86_64-linux/rbconfig.rb: $${MODULE_DIR}/upstream/ruby/rbconfig.rb' >> usr.manifest
	echo '/usr/lib/ruby/2.1.0/x86_64-linux/**: $${MODULE_DIR}/upstream/ruby/.ext/x86_64-linux/**' >> usr.manifest
	echo '/usr/local/ssl/cert.pem: $${MODULE_DIR}/upstream/cert.pem' >> usr.manifest
	find upstream/ruby/.ext/x86_64-linux/ -name '*.so' -exec ldd {} \;|awk '{print $$1,":",$$3}'|grep "/lib"|grep -v "ld-linux"|grep -v "libc.so"|grep -v "libpthread.so"|grep -v "libdl.so"|grep -v "libm.so"|sort|uniq|sed -e "s/ //" \
		>> usr.manifest
	: > bootfs.manifest

ROOTFS: module
	mkdir -p ./ROOTFS/usr/lib/ruby/2.1.0/x86_64-linux
	mkdir -p ./ROOTFS/usr/local/ssl
	cp -a ./upstream/ruby/.ext/common/* ./ROOTFS/usr/lib/ruby/2.1.0
	cp -a ./upstream/bundler/lib/* ./ROOTFS/usr/lib/ruby/2.1.0
	cp ruby.so ./ROOTFS/
	cp -a ./upstream/ruby/bin/* ./ROOTFS/
	cp ./upstream/ruby/libruby.so ./ROOTFS/libruby.so.2.1
	cp -a ./upstream/ruby/lib/* ./ROOTFS/usr/lib/ruby/2.1.0
	cp ./upstream/ruby/rbconfig.rb ./ROOTFS/usr/lib/ruby/2.1.0/x86_64-linux/rbconfig.rb
	cp -a ./upstream/ruby/.ext/x86_64-linux/* ./ROOTFS/usr/lib/ruby/2.1.0/x86_64-linux/
	cp ./upstream/cert.pem ./ROOTFS/usr/local/ssl/cert.pem
	find upstream/ruby/.ext/x86_64-linux/ -name '*.so' -exec ldd {} \;|awk '{print "cp",$$3,"./ROOTFS/"}'|grep "/lib"|grep -v "ld-linux"|grep -v "libc.so"|grep -v "libpthread.so"|grep -v "libdl.so"|grep -v "libm.so"|grep -v "libruby.so"|sort|uniq > tmp.sh
	sh tmp.sh
	rm tmp.sh

.PHONY: clean
clean:
	rm -rf upstream *.o *.so usr.manifest ROOTFS
