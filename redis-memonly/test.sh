#!/bin/bash

THIS_DIR=$(readlink -f $(dirname $0))
CMDLINE=$($THIS_DIR/../cmdline.sh $THIS_DIR)

$THIS_DIR/../../scripts/tests/test_app_with_test_script.py \
  -e "$CMDLINE" \
  --guest_port 6379 \
  --host_port 6379 \
  --start_line 'The server is now ready' \
  --script_path $THIS_DIR/tester.py
