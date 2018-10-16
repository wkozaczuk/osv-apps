#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
   MonoDomain *domain;
   MonoAssembly *assembly;
   int retval;

   domain = mono_jit_init_version("hello.exe", "v4.0.30319");
   assembly = mono_domain_assembly_open(domain, "hello.exe");
   if (!assembly)
      exit(2);

   retval = mono_jit_exec (domain, assembly, argc - 1, argv + 1);
   mono_jit_cleanup(domain);

   return retval;
}
