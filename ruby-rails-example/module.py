from osv.modules import api

api.require('ruby')
default = api.run(cmdline="--cwd=/osv_test/ --env=GEM_HOME=/osv_test/vendor/bundle/ruby /ruby.so ./bin/rails server")
