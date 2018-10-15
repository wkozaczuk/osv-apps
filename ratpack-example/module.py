from osv.modules import api

api.require('java8')

default = api.run('/java.so -Xms128m -Xmx128m -jar ratpack.jar')
