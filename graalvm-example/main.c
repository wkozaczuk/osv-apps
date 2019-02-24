//
// Copyright (C) 2018 Waldek Kozaczuk
//
// This work is open source software, licensed under the terms of the
// BSD license as described in the LICENSE file in the top-level directory.
//
#include <stdlib.h>
#include <stdio.h>

#include <libhello.h>

int main(int argc, char **argv) {
  graal_isolate_t *isolate = NULL;
  graal_isolatethread_t *thread = NULL;
  
  if (graal_create_isolate(NULL, &isolate, &thread) != 0) {
    fprintf(stderr, "initialization error\n");
    return 1;
  }
  
  graal_main(thread);
  return 0;
}
