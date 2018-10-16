.PHONY: module
module: mono_exec

#CFLAGS = -std=gnu99 -fpie -rdynamic
CFLAGS=-std=gnu99 -fpie -rdynamic `pkg-config --cflags mono-2`
LDFLAGS=-pie `pkg-config --libs mono-2`

mono_exec: mono_exec.c
	$(CC) -o $@ $(CFLAGS) mono_exec.c $(LDFLAGS)
	#$(CC) -pie -o $@ $(CFLAGS) $(LDFLAGS) mono_exec.c

clean:
	rm -f mono_exec
