from osv.modules import api

api.require('java')

default = api.run(
' --cwd=/elasticsearch '
'  /java.so '
'  -Xms256m '
'  -Xmx1g '
'  -Djava.awt.headless=true '
'  -XX:+UseParNewGC '
'  -XX:+UseConcMarkSweepGC '
'  -XX:CMSInitiatingOccupancyFraction=75 '
'  -XX:+UseCMSInitiatingOccupancyOnly '
'  -XX:+HeapDumpOnOutOfMemoryError '
'  -XX:+DisableExplicitGC '
'  -Dfile.encoding=UTF-8 '
'  -Dosv.java.diagnostics '
'  -Djna.nosys=true '
'  -Des.insecure.allow.root=true '
'  -Des.path.home=/elasticsearch '
'  -Des.foreground=true '
' -cp /elasticsearch/lib/elasticsearch-2.4.0.jar:/elasticsearch/lib/* '
' org.elasticsearch.bootstrap.Elasticsearch '
' start ')
