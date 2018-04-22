.PHONY: module
module: target/release/libhttpserver.so
	echo '/libhttpserver.so: $${MODULE_DIR}/target/release/libhttpserver.so' > usr.manifest

target/release/libhttpserver.so: src/lib.rs
	cargo build --release

clean:
	cargo clean	
	rm -f usr.manifest
