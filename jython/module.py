from osv.modules import api

api.require('jre')

default = api.run_java(args=['-jar', 'jython.jar', '-m', 'SimpleHTTPServer', '8888'])
