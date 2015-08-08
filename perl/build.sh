#!/bin/sh
#
#build.sh - build images for various hypervisor targets.
#

hypervisors="qemu vbox vmw gce"
hypervisors="vmw"

for target in $hypervisors 
do
    echo capstan build -p $target -v perl-base
    capstan build -p $target -v perl-base
done
