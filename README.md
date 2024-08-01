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

### Update 1:
While we are not using 64bit memory here and only 64bit values, it turned out that -wasm64 would be specified if MEMORY64 is in the [settings](https://github.com/emscripten-core/emscripten/blob/9b99b5d811e1513914942da0a81e36bc333d3115/tools/building.py#L285).

But that that would give us the FRONZEN_CACHE error again.

Although, I also found that we can specify a secondary cache where we can pass in wasm64 as a configuration option. I also learned that every module that would be flagged as missing in the frozen cache should be added to the target like so:

```skylark
register_emscripten_toolchains(cache = {
     "configuration": ["--wasm64"],
     "targets": [
         "libprintf_long_double",
         "libembind-rtti",
         "libGL-getprocaddr",
         "libal",
         "libhtml5",
         "libstubs",
         "libnoexit",
         "libc",
         "libemmalloc",
         "libcompiler_rt",
         "libc++-noexcept",
         "libc++abi-noexcept",
         "libsockets"
     ]
 })
```

Now the BIGINT isn't required anymore and we can compile the code without errors! The only annoying thin is that we have to specify experimental feature flags in the browser to run the code:
- `chrome://flags/#experimental-wasm-memory64`
- `chrome://flags/#enable-experimental-webassembly-features`

At least it works! Let's see if we can get rid of the 64 bit memory and *only* use 64 bit values.