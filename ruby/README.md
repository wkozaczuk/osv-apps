# CRuby on OSv

This is a porting CRuby for OSv.

## Prerequires

You need to install same version of Ruby on host side, before building CRuby for OSv.
This is mandatory to keep C extension compatibility.
You can use version management tool like rvm.

Example:
```
\curl -sSL https://get.rvm.io | bash -s stable
source ~/.profile

rvm install ruby-2.2.2
```

## Try irb on OSv

You can try irb by following command:
```
./scripts/run.py -e '/ruby.so /irb'
```

## Sample scripts

You can find more sample scripts on ruby-example module.
