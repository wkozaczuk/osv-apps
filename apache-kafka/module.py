from osv.modules import api

api.require('jre')

default = api.run(
    '--cwd=/kafka '
    '/java.so '
    '-Xmx1G '
    '-Xms1G '
    '-XX:+UseParNewGC '
    '-XX:+UseConcMarkSweepGC '
    '-XX:+CMSClassUnloadingEnabled '
    '-XX:+CMSScavengeBeforeRemark '
    '-XX:+DisableExplicitGC '
    '-Djava.awt.headless=true '
    '-Xloggc:/kafka/logs/kafkaServer-gc.log '
    '-verbose:gc '
    '-XX:+PrintGCDetails '
    '-XX:+PrintGCDateStamps '
    '-XX:+PrintGCTimeStamps '
    '-Dcom.sun.management.jmxremote '
    '-Dcom.sun.management.jmxremote.authenticate=false '
    '-Dcom.sun.management.jmxremote.ssl=false '
    '-Dkafka.logs.dir=/kafka/logs '
    '-Dlog4j.configuration=file:/kafka/config/log4j.properties '
    '-cp :/kafka/core/build/dependant-libs-2.10.4*/*.jar:/kafka/contrib/hadoop-consumer/build/libs/kafka-hadoop-consumer*.jar:/kafka/contrib/hadoop-producer/build/libs/kafka-hadoop-producer*.jar:/kafka/clients/build/libs/kafka-clients*.jar:/kafka/libs/jopt-simple-3.2.jar:/kafka/libs/kafka_2.10-0.8.2.1.jar:/kafka/libs/kafka-clients-0.8.2.1.jar:/kafka/libs/log4j-1.2.16.jar:/kafka/libs/lz4-1.2.0.jar:/kafka/libs/metrics-core-2.2.0.jar:/kafka/libs/scala-library-2.10.4.jar:/kafka/libs/slf4j-api-1.7.6.jar:/kafka/libs/slf4j-log4j12-1.6.1.jar:/kafka/libs/snappy-java-1.1.1.6.jar:/kafka/libs/zkclient-0.3.jar:/kafka/libs/zookeeper-3.4.6.jar:/kafka/core/build/libs/kafka_2.10*.jar '
    'kafka.Kafka /kafka/config/server.properties'
)
