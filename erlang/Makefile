.PHONY: all

OTP_VERSION=17.3
ERTS_VERSION=6.2

all: install erlang.so
module: install erlang.so

otp_src_$(OTP_VERSION).tar.gz:
	wget -O "$@.temp" "http://www.erlang.org/download/otp_src_$(OTP_VERSION).tar.gz"
	mv "$@.temp" "$@"

otp_src_$(OTP_VERSION): otp_src_$(OTP_VERSION).tar.gz
	tar xvf "$<"
	touch otp_src_$(OTP_VERSION)/lib/os_mon/c_src/disksup.c
	patch -b -p0 < os_mon.patch
	patch -b -p0 < epmd.patch

configure: otp_src_$(OTP_VERSION)
	cd otp_src_$(OTP_VERSION); export ERL_TOP=$(CURDIR)/otp_src_$(OTP_VERSION) CFLAGS=-fpie LDFLAGS="-pie -rdynamic"; ./configure -prefix=/usr --libdir=/usr/lib64 --disable-hipe --without-hipe --without-odbc --enable-builtin-zlib --without-termcap --without-wx --without-erl_interface --without-javac --without-jinterface

compile: configure
	mkdir -p ROOTFS
	cd otp_src_$(OTP_VERSION); export ERL_TOP=$(CURDIR)/otp_src_$(OTP_VERSION); $(MAKE)

install: compile
	cd otp_src_$(OTP_VERSION); export ERL_TOP=$(CURDIR)/otp_src_$(OTP_VERSION) DESTDIR=$(CURDIR)/ROOTFS; make install
	find ROOTFS -name '*.so' | xargs -I {} ldd {} | grep -Po '(?<=> )/[^ ]+' | sort | uniq | grep -Pv 'lib(c|dl|m|util|rt|pthread).so' | xargs -I {} install -D -T {} ROOTFS{}

erlang.so: erlang.c
	$(CC) -shared -rdynamic -fPIC -o erlang.so -std=gnu99 -DERTS_VERSION=$(ERTS_VERSION) erlang.c

clean:
	-rm -rf ROOTFS
	-rm -rf otp_src_$(OTP_VERSION)
	-rm -f otp_src_$(OTP_VERSION).tar.gz otp_src_$(OTP_VERSION).tar.gz.temp erlang.so
