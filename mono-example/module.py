from osv.modules import api

default = api.run("--env=MONO_DISABLE_SHARED_AREA=true /mono_exec hello.exe")
