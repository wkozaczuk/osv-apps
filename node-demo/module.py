from osv.modules import api

api.require('node')

default = api.run(cmdline="/libnode.so /express/examples/hello-world")
