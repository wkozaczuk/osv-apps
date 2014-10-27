.PHONY: module test browser_test clean
module: ROOTFS usr.manifest

PUBLIFY_VER=v8.0.2

sqlite-autoconf-3080500.tar.gz:
	wget "http://www.sqlite.org/2014/sqlite-autoconf-3080500.tar.gz"

sqlite-autoconf-3080500: sqlite-autoconf-3080500.tar.gz
	tar xvf sqlite-autoconf-3080500.tar.gz
sqlite-autoconf-3080500/.libs/libsqlite3.so.0.8.6: sqlite-autoconf-3080500
	cd sqlite-autoconf-3080500 && ./configure && make CFLAGS="-fPIC -DHAVE_MREMAP=0"
	
ROOTFS/libsqlite3.so.0: sqlite-autoconf-3080500/.libs/libsqlite3.so.0.8.6
	cp sqlite-autoconf-3080500/.libs/libsqlite3.so.0.8.6 ROOTFS/libsqlite3.so.0
tmp/bin/bundle: 
	GEM_HOME=tmp gem install bundler
tmp/bin/rake:
	GEM_HOME=tmp gem install rake
publify:
	git clone -b ${PUBLIFY_VER} https://github.com/publify/publify.git
	rm publify/config/environments/production.rb
ROOTFS/publify: publify tmp/bin/bundle tmp/bin/rake
	mkdir -p ROOTFS
	cp -a publify ROOTFS/
	cd ROOTFS/publify && patch -p1 < ../../publify.patch
ROOTFS/publify/config/database.yml:
	cp database.yml ROOTFS/publify/config/database.yml
ROOTFS/publify/config/environments/production.rb:
	cp production.rb ROOTFS/publify/config/environments/production.rb
ROOTFS/publify/vendor/bundle/ruby/2.1.0/bin/rake:
	cd ROOTFS/publify && env GEM_HOME=vendor/bundle/ruby/2.1.0 gem install rake

ROOTFS/publify/bin/rails:
	mkdir -p ROOTFS/publify/bin
	cp rails ROOTFS/publify/bin

ROOTFS/publify/vendor/bundle: ROOTFS/publify ROOTFS/publify/config/database.yml ROOTFS/publify/config/environments/production.rb ROOTFS/publify/vendor/bundle/ruby/2.1.0/bin/rake ROOTFS/publify/bin/rails
	cd ROOTFS/publify && env GEM_HOME=../../tmp ../../tmp/bin/bundle install --path vendor/bundle
	cd ROOTFS/publify && env GEM_HOME=vendor/bundle/ruby/2.1.0 gem install tzinfo-data turbolinks carrierwave addressable bundler json
	cd ROOTFS/publify && env GEM_HOME=vendor/bundle/ruby/2.1.0 gem install will_paginate -v 3.0.pre4
	cd ROOTFS/publify && env GEM_HOME=vendor/bundle/ruby/2.1.0 vendor/bundle/ruby/2.1.0/bin/rake db:create RAILS_ENV=production
	cd ROOTFS/publify && env GEM_HOME=vendor/bundle/ruby/2.1.0 vendor/bundle/ruby/2.1.0/bin/rake db:migrate RAILS_ENV=production
	cd ROOTFS/publify && env GEM_HOME=vendor/bundle/ruby/2.1.0 vendor/bundle/ruby/2.1.0/bin/rake db:seed RAILS_ENV=production
	cd ROOTFS/publify && env GEM_HOME=vendor/bundle/ruby/2.1.0 vendor/bundle/ruby/2.1.0/bin/rake assets:precompile
ROOTFS: ROOTFS/publify/vendor/bundle ROOTFS/libsqlite3.so.0

usr.manifest:
	echo '/publify/**: $${MODULE_DIR}/ROOTFS/publify/**' >> usr.manifest
	echo '/libsqlite3.so.0: $${MODULE_DIR}/sqlite-autoconf-3080500/.libs/libsqlite3.so.0.8.6' >> usr.manifest
	find ROOTFS/publify/vendor/bundle -name '*.so' -exec ldd {} \;|awk '{print $$1,":",$$3}'|grep "/lib64"|grep -v "ld-linux"|grep -v "libc.so"|grep -v "libpthread.so"|grep -v "libdl.so"|grep -v "libm.so"|grep -v "libstdc++"|grep -v "libgcc_s"|grep -v "librt"|grep -v "sqlite3"|grep -v "libssl.so"|sort|uniq|sed -e "s/ //" \
		>> usr.manifest

test:
	python test.py

browser_test:
	Xvfb :1 -screen 0 1024x768x24 &
	env DISPLAY=:1 python browser_test.py
	killall Xvfb

clean:
	rm -rf usr.manifest sqlite-autoconf-3080500 *.tar.gz ROOTFS tmp publify
