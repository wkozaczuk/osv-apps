.PHONY: module
module: target/release/libhello.so
	echo '/libhello.so: $${MODULE_DIR}/target/release/libhello.so' > usr.manifest

target/release/libhello.so: src/lib.rs
	(command -v cargo && cargo build --release) || echo "Please install Rust to build this app"

clean:
	(command -v cargo && cargo clean) || echo > /dev/null
	rm -f usr.manifest
