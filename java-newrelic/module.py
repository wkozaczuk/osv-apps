from osv.modules import api

api.require('jre')
default = api.run_java(jvm_args=['-javaagent:/usr/newrelic.jar'])
