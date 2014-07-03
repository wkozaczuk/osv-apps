from osv.modules import api

api.require('ruby')
default = api.run(cmdline="--cwd=/publify/ --env=GEM_HOME=/publify/vendor/bundle/ruby /ruby.so ./bin/rails server -e production")
