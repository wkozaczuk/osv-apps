#!/bin/bash

THIS_DIR=$(readlink -f $(dirname $0))
ZOOKEEPER_CMDLINE=$($THIS_DIR/../cmdline.sh $THIS_DIR 'zookeeper')

$THIS_DIR/../../scripts/tests/test_app.py -e "$ZOOKEEPER_CMDLINE" \
  -i /media/wkozaczuk/CrossSpace/capstan_repo_20190912/repository/kafka/kafka.qemu \
  --host_port 2181 \
  --guest_port 2181 \
  --line 'Hello World from Zookeeper' &
ZOOKEEPER_PID=$!

KAFKA_CMDLINE=$($THIS_DIR/../cmdline.sh $THIS_DIR 'native')
$THIS_DIR/../../scripts/tests/test_app.py -e "$KAFKA_CMDLINE" \
  --host_port 8080 \
  --guest_port 8080 \
  --line 'Hello World from Kafka'
