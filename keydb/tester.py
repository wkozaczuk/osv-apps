import sys
import subprocess

success = False

print("Started keydb test ...")
try:
   output = subprocess.check_output(["redis-benchmark", "-t", "set,lpush", "-n", "100000", "-q"], stderr=subprocess.STDOUT).decode()
   print(output)

   if 'requests per second' in output:
      success = True
except subprocess.CalledProcessError as err:
   print(err.output)
