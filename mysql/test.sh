#!/bin/bash

THIS_DIR=$(readlink -f $(dirname $0))
CMDLINE=$($THIS_DIR/../cmdline.sh $THIS_DIR)

$THIS_DIR/../../scripts/tests/test_app_with_test_script.py \
  -e "$CMDLINE" \
  --guest_port 3306 \
  --host_port 3306 \
  --start_line 'ready for connections' \
  --script_path $THIS_DIR/tester.py
