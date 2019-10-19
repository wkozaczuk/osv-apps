import sys
import subprocess

success = False

print("Started mysql test ...")
try:
   output = subprocess.check_output(["/home/wkozaczuk/projects/osv/apps/mysql/sysbench.sh"], stderr=subprocess.STDOUT)
   print(output)

   if 'execution time' in output:
      success = True
except subprocess.CalledProcessError as err:
   print(err.output)
