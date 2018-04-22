extern crate rustc_version_runtime;
use rustc_version_runtime::version;

// This is the main function
#[no_mangle]
pub extern fn main() {
    // The statements here will be executed when the compiled binary is called

    // Print text to the console
    println!("Hello World from Rust {:?} on OSv!", version());
}
