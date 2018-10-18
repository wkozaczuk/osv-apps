.PHONY: module
module: ROOTFS/run_mono ROOTFS/hello.exe

CFLAGS=-std=gnu99 -fpie -rdynamic `pkg-config --cflags mono-2`
LDFLAGS=-pie `pkg-config --libs mono-2`

ROOTFS/run_mono: run_mono.c
	mkdir -p ROOTFS
	pkg-config --exists mono-2 || echo "Please install mono2. For details read https://www.mono-project.com/download/stable/#download-lin"
	$(CC) -o $@ $(CFLAGS) run_mono.c $(LDFLAGS)

ROOTFS/hello.exe: hello.cs
	mkdir -p ROOTFS
	csc hello.cs /out:ROOTFS/hello.exe

clean:
	rm -rf ROOTFS
