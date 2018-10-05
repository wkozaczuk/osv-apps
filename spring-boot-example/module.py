from osv.modules import api

api.require('java')

default = api.run('/java.so -Xms64m -Xmx64m -jar spring-boot-2-rest-service-basic.jar')
