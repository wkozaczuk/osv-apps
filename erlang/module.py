from osv.modules import api

api.require("openssl")
api.require("libz")
default = api.run(cmdline="/usr/lib64/erlang.so -env HOME / /etc/erlang/vm.args /etc/default/erlang/vm.args")
