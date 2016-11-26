from osv.modules import api

api.require('jre')

default = api.run_java(args=['-jar', 'start.jar'])
