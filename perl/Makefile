#no tabs, like capstan:
.RECIPEPREFIX := $(shell printf " ")

.DEFAULT_GOAL := perl

PERLSRC_VERS = 5.20.2
PERLSRC_DIST = perl_$(PERLSRC_VERS).orig.tar.bz2
WGET_URL     = http://ftp.us.debian.org/debian/pool/main/p/perl/$(PERLSRC_DIST)

OSV_FLAGS       := -std=gnu99 -fpie -rdynamic -pie
PERL_LDFLAGS    := -ldl -lm -lc -lcrypt 

CONFIGURE_FLAGS := -des -Duseshrplib -Ud_sigsetjmp -Dprefix=/osv -Dsiteprefix=/osv/opt -Dldflags="$(OSV_FLAGS)" -Dccflags=-fPIC
INSTALL_FLAGS   := DESTDIR=../ROOTFS

perl: getdist configure perl/libperl.so

#install.perl target only installs perl, not manuals
install: perl
    cd perl && make $(INSTALL_FLAGS) install.perl

#ORIG:  cc -o perl -fstack-protector -L/usr/local/lib -Wl,-E -Wl,-rpath,/usr/local/lib/perl5/5.20.2/x86_64-linux/CORE perlmain.o  libperl.so `cat ext.libs` -lnsl -ldl -lm -lcrypt -lutil -lc 

perl/libperl.so:
    cd perl && make

getdist: $(PERLSRC_DIST) perl/Configure

perl/Configure:
    tar xf $(PERLSRC_DIST)
    mv perl-$(PERLSRC_VERS) perl

$(PERLSRC_DIST):
    wget $(WGET_URL)

configure: perl/Configure perl/config.h

perl/config.h:
    cd perl && ./Configure $(CONFIGURE_FLAGS)

clean:
    rm -rf perl usr.manifest ROOTFS

deepclean: clean
    rm -f $(PERLSRC_DIST)
