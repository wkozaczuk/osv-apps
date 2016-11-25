from osv.modules import api

api.require('jre')

default = api.run_java(classpath=['/java-example'], args=['Hello'])
