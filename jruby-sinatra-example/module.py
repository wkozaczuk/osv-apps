from osv.modules import api

api.require('jre')

default = api.run_java(args=['-jar', 'jruby-complete.jar', '-I./', '-rjruby-extensions.jar', 'example.rb'])
