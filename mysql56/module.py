from osv.modules import api

default = api.run("/usr/bin/mysqld --datadir=/usr/data --user=root")
