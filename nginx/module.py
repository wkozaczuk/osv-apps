from osv.modules import api

default = api.run('/nginx.so -c /nginx/conf/nginx.conf')
