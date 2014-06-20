from osv.modules import api

default = api.run(cmdline="/memcached -t 1 -u root")
