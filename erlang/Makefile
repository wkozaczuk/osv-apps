.PHONY: all

OTP_VERSION=17.3

all: install
module: install

otp_src_$(OTP_VERSION).tar.gz:
	wget -O "$@.temp" "http://www.erlang.org/download/otp_src_$(OTP_VERSION).tar.gz"
	mv "$@.temp" "$@"

otp_src_$(OTP_VERSION): otp_src_$(OTP_VERSION).tar.gz
	tar xvf "$<"

configure: otp_src_$(OTP_VERSION)
	cd otp_src_$(OTP_VERSION); export ERL_TOP=$(CURDIR)/otp_src_$(OTP_VERSION) CFLAGS=-fpie LDFLAGS=-pie; ./configure -prefix=/usr --libdir=/usr/lib64 --disable-hipe --without-hipe --without-odbc --without-os_mon --enable-builtin-zlib --without-termcap --without-wx --without-erl_interface --without-javac --without-jinterface

compile: configure
	mkdir -p ROOTFS
	cd otp_src_$(OTP_VERSION); export ERL_TOP=$(CURDIR)/otp_src_$(OTP_VERSION); $(MAKE)

install: compile
	cd otp_src_$(OTP_VERSION); export ERL_TOP=$(CURDIR)/otp_src_$(OTP_VERSION) DESTDIR=$(CURDIR)/ROOTFS; make install
	find ROOTFS -name '*.so' | xargs -I {} ldd {} | grep -Po '(?<=> )/[^ ]+' | sort | uniq | grep -Pv 'lib(c|dl|m|util|rt|pthread).so' | xargs -I {} install -D -T {} ROOTFS{}
	make -C os_mon
	mkdir -p $(CURDIR)/ROOTFS/usr/lib64/erlang/lib/os_mon-2.3
	cd os_mon; cp --parents -u -r -t $(CURDIR)/ROOTFS/usr/lib64/erlang/lib/os_mon-2.3 ebin/* src/* priv/*

clean:
	-rm -rf ROOTFS
	-rm -rf otp_src_$(OTP_VERSION)
	-rm -f otp_src_$(OTP_VERSION).tar.gz otp_src_$(OTP_VERSION).tar.gz.temp
