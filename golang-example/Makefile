.PHONY: module
module: hello
	echo '/hello: $${MODULE_DIR}/hello' > usr.manifest

hello: hello.go
	go build -buildmode=c-shared hello.go

clean:
	rm -f hello usr.manifest
