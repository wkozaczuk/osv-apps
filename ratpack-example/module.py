from osv.modules import api

api.require('java8')

default = api.run('/java.so -cp /ratpack org.springframework.boot.loader.JarLauncher')
