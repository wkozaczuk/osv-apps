from osv.modules import api

api.require('openjdk8-zulu-compact2')

default = api.run('/java.so -cp /java-example Hello')
