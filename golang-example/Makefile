.PHONY: module
module: hello
	echo '/hello: $${MODULE_DIR}/hello' > usr.manifest

hello: hello.go
	/usr/lib/golang/bin/go build -buildmode=c-shared hello.go

clean:
	rm -f hello usr.manifest
