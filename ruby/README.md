# CRuby on OSv

This is a porting CRuby for running some application on OSv.

## Building

You need to install some packages for build CRuby.

**Fedora**

```
yum install wget patch ruby-devel openssl-devel
```

**Arch Linux**
```
pacman -S wget ruby openssl
```

And you also need suggest image when you build OSv

```
make image=ruby
```

## Running OSv

This module has irb

You can launch this command:
```
./scripts/run.py -e '/ruby.so /irb'
```
