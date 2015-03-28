from osv.modules import api

default = api.run_java(
    jvm_args=[
        '-Xms512m',
        '-Xmx512m',
        '-Dscala.usejavacp=true',
        '--class org.apache.spark.repl.Main',
    ],
    classpath=[
        '/spark/conf',
        '/spark/lib/spark-assembly-1.3.0-hadoop2.4.0.jar',
        '/spark/lib/datanucleus-core-3.2.10.jar',
        '/spark/lib/datanucleus-rdbms-3.2.9.jar',
        '/spark/lib/datanucleus-api-jdo-3.2.6.jar',
    ],
    args=[
        'org.apache.spark.deploy.SparkSubmit',
        'spark-shell',
    ]
)
