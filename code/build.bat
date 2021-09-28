clang --target=wasm32-unknown-unknown-wasm -O2 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -Wno-static-in-inline -o ../build/app.wasm web_app.c
