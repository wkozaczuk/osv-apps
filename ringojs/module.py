from osv.modules import api

api.require('jre')

default = api.run_java(classpath=['/lib/js.jar'], args=['-jar', '/run.jar', '/examples/httpserver.js'])
