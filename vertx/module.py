from osv.modules import api

api.require('java')

default = api.run('/java.so -Xms64m -Xmx64m -Dvertx.disableDnsResolver=true -jar HelloWorld.jar')
