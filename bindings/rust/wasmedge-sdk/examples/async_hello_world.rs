use wasmedge_sdk::{
    async_host_function, error::HostFuncError, params, Caller, ImportObjectBuilder, Vm, WasmValue,
};

#[async_host_function]
fn say_hello(caller: Caller, _args: Vec<WasmValue>) -> Result<Vec<WasmValue>, HostFuncError> {
    tokio::time::sleep(std::time::Duration::from_secs(1)).await;
    println!("Hello, world!");

    // get executor from caller
    let executor = caller.executor();
    assert!(executor.is_some());

    // get module instance from caller
    let instance = caller.instance();
    if let Some(instance) = instance {
        assert_eq!(instance.name(), Some("extern".to_string()));
        assert_eq!(instance.func_count(), 1);
        assert_eq!(instance.memory_count(), 0);
        assert_eq!(instance.global_count(), 0);
        assert_eq!(instance.table_count(), 0);
    }

    // get memory from caller
    let mem = caller.memory(0);
    assert!(mem.is_none());

    Ok(vec![])
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    // create an import module
    let import = ImportObjectBuilder::new()
        .with_func_async::<(), ()>("say_hello", say_hello)?
        .build("extern")?;

    let vm = Vm::new(None)?.register_import_module(import)?;

    tokio::spawn(async move {
        let _ = vm
            .run_func_async(Some("extern"), "say_hello", params!())
            .await
            .unwrap();
    })
    .await?;
    println!("main thread");
    Ok(())
}
