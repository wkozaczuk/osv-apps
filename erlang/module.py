from osv.modules import api

default = api.run(cmdline="--env=BINDIR=/usr/lib64/erlang/erts-6.2/bin /usr/lib64/erlang/erts-6.2/bin/beam -- -root /usr/lib/erlang -progname erl -- -home / --")
