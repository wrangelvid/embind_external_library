# A minimal example to include external libraries with

According to the standard Emscripten [documentation](https://emscripten.org/docs/compiling/Building-Projects.html#using-libraries), the typical approach involves building the libraries to object files or archives and then linking them with the main program to emit JavaScript and WebAssembly.
But we are using Bazel, which handles the linking and compilation for us.
1. Let's make sure we can compile and run the example program without the external library.
```bash
bazel run //module:hello_test
```
This should print out `Yo! Bob`.

2. Now let's try to bind this with emscripten
```bash
bazel build //module:hello_wasm
```
This should run through without any issues.

3. It's time to include an external library. I have chosen to include the [fmt](https://github.com/fmtlib/fmt)
```bash
bazel run //module:hello_external_test
```
This should print out `Sneaky Hello Message!` and `Yo! Bob`.

4. Now let's try to bind this with emscripten
```bash
bazel build //module:hello_external_wasm
```
Oh, well that works too!

