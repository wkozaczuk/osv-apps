.PHONY: module
module: target/release/libhello.so
	echo '/libhello.so: $${MODULE_DIR}/target/release/libhello.so' > usr.manifest

target/release/libhello.so: src/lib.rs
	cargo build --release

clean:
	cargo clean
	rm -f usr.manifest
