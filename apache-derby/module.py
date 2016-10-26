from osv.modules import api

api.require('java')

_classpath = ["/db-derby/lib/derby.jar", "/db-derby/lib/derbynet.jar", "/db-derby/lib/derbytools.jar", "/db-derby/lib/derbyclient.jar"]
_args = ["-Djava.security.policy=/db-derby/security.policy", "org.apache.derby.drda.NetworkServerControl", "start"]

default = api.run_java(classpath = _classpath, args = _args)

