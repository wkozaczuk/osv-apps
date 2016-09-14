from osv.modules import api

api.require('openjdk8-zulu-compact1')

default = api.run('/java.so -cp /java-example Hello')
