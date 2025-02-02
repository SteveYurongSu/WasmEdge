//! This example demonstrates the concurrent execution of multiple host functions with `Vm::run_func_async` API.
//!
//! To run this example, use the following command:
//! ```bash
//! cd <wasmedge-root-dir>/bindings/rust/
//! cargo run -p wasmedge-sdk --example async_run_func
//! ```

use wasmedge_sdk::{
    config::{CommonConfigOptions, ConfigBuilder},
    params, Vm, WasmVal,
};

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let wasm_file = std::path::PathBuf::from(env!("WASMEDGE_DIR"))
        .join("bindings/rust/wasmedge-sys/tests/data/fibonacci.wasm");

    let config = ConfigBuilder::new(CommonConfigOptions::default()).build()?;
    assert!(config.bulk_memory_operations_enabled());

    // create Vm instance
    let vm = Vm::new(Some(config))?.register_module_from_file("extern", wasm_file)?;

    // async run function
    let fut1 = vm.run_func_async(Some("extern"), "fib", params!(20));

    let fut2 = vm.run_func_async(Some("extern"), "fib", params!(5));

    let returns = tokio::join!(fut1, fut2);

    let (ret1, ret2) = returns;
    let returns1 = ret1?;
    assert_eq!(returns1[0].to_i32(), 10946);
    let returns2 = ret2?;
    assert_eq!(returns2[0].to_i32(), 8);

    Ok(())
}
