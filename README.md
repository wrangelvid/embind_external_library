# A repository to reproduce and fix a few issues I encountered while playing with Bazel and Emscripten

## Compiling 64 bit code with Emscripten.
Some libraries demand a 64 bit architecture. For instance, some use hashing algorithms like `FNV1aHasher` with a 64 bits to reduce the likelihood for collisions. Well, we could do some shenanigans to apply transformations to the code to make it work with 32 bits, but that's not the point of this branch (hopefully I don't have to do that).

First, let's build and test the code without emscripten:
```bash
bazel run //module:hello_test
```
Which should print out that it's running on a 64 bit architecture.

Now let's try to bind the code with emscripten:
```bash
bazel build //module:hello_wasm
```
and we get an error that `size_t` is not 64 bit, even though we set `MEMORY64=1` and `WASM_BIGINT=1` in the EMCC_SETTINGS.

Alright, let's try to compile the code with a 64 bit architecture:
```bash
bazel build --copt=-m64 //module:hello_wasm
```

Great, we got a little further, however now you should see:

`Exception: FROZEN_CACHE is set, but cache file is missing`

If we remove `-s MEMORY64=1` from the EMCC_SETTINGS, we get:

`wasm-ld: error: bazel-out/wasm-opt-ST-***/bin/module/_objs/hello_embind/hello_js.o: must specify -mwasm64 to process wasm64 object files`


