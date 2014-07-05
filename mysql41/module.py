from osv.modules import api

default = api.run("--cwd=/mysql41 ./mysqld --pid-file=mysqld.pid --datadir=./data")
