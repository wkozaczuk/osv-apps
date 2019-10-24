import sys
import subprocess

success = False

print("Started iperf3 test ...")
try:
   output = subprocess.check_output(["iperf3", "-t", "5", "-c", "localhost"], stderr=subprocess.STDOUT)
   print(output)

   if 'iperf Done' in output:
      success = True
except subprocess.CalledProcessError as err:
   print(err.output)
