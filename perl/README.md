# Perl on OSv

This is a port of Perl 5.20.2 for OSv.

## Prerequisites

This port only requires the standard tools that you would use to build any version of perl.
You will also need a standard OSv development environement set up.

I started with a minimal debian 8 install from:

     debian-live-8.1.0-amd64-standard.iso

Development was done from a VM build from above ISO, using VMware Fusion 7.1.1.

I tested using a shared CAPSTAN_ROOT between debian and host Mac.
For this to work, you have to install open-vm-tools on debian,
and then share a common folder from VMware fusion.

## How to build

I have included a ./build.sh script to show the top level build using Capstan.

All work is done by the Makefile.

The "install" target will fetch the source bundle, untar it, configure it, compile it,
and install the result under ./ROOTFS/osv.

I chose /osv as the root directory to enable easier testing on linux - I just symlink
/osv on linux to point to my ROOTFS, for example:

    /osv -> /home/russt/proj/osv-apps/perl/ROOTFS/osv/

Then add /osv/bin/ to your path, and the environment will work on linux with all
perl libraries in the correct location.  We have linked all the commands using the
gcc PIE (position independent executable) options, which allows the resultant
binaries to run under linux as well as OSv.  The results should look like this:

$ file `which perl`
/osv/bin/perl: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked,
     interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32,
     BuildID[sha1]=ad806a3acd092c93b6eeebb4e9430760482ac6b5, not stripped

The trick on the linux side is the "interpreter", which is a stub that will load the
shared object for you.

And it will work on OSv in the same way.

Of course you will have to be careful about extra external libraries getting picked up
when testing on the linux side.

## How to configure

If you adjust any of the configuration options (there are 1,098 of them), do a clean build:

    make clean configure

This will reload the perl source distribution and reconfigure from scratch.
On my debian VM, it takes about 28 seconds.

If you need to adjust the configuration, please see: perl/Porting/Glossary
This file is quite helpful in describing all the possible options.

Also, please see perl/INSTALL, as it describes many of the more common options.

## How to Test

Testing for OSv is a challenge.  However, since it has binary compatibility with linux,
you can test many things on linux using the perl-base image we are building.

## Sample scripts

Once you have built this image (perl-base), you should be able to build the perl-hello example,
and the perl-debugger interactive loop example.
