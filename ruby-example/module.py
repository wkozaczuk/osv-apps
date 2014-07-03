from osv.modules import api

api.require('ruby')
default = api.run(cmdline="/ruby.so /ruby-example/hello.rb")
