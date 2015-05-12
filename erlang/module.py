from osv.modules import api

default = api.run(cmdline="--env=BINDIR=/usr/lib64/erlang/erts-6.2/bin --env=HOME=/ /usr/lib64/erlang/erts-6.2/bin/erlexec +K true -name foo@127.0.0.1")
