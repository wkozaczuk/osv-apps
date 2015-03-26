/* 
 * When compiling a Go program with gccgo, the main() is normally picked up
 * from libgobegin.a. Unfortunately, this library is compiled without -fPIC
 * so we cannot use it in OSv, so we need to supply our own main() function.
 *
 * This is a minimal version of gccgo's runtime/go-main.c.
 */

#include <stdlib.h>
#include <stdint.h>

/* The various functions from libgo do all the work */
extern void runtime_check(void);
extern void runtime_args(uint32_t, uint8_t**);
extern void runtime_osinit(void);
extern void runtime_schedinit(void);
extern struct G* __go_go(void (*pfn)(void*), void*);
extern void* runtime_mstart(void*);
extern void runtime_main(void*);
extern struct M* runtime_m(void);

int
main (int argc, char **argv)
{
  runtime_check ();
  runtime_args (argc, (uint8_t**) argv);
  runtime_osinit ();
  runtime_schedinit ();
  __go_go (runtime_main, NULL);
  runtime_mstart (runtime_m ());
  abort ();
}
