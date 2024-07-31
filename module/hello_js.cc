#include <emscripten/bind.h>
#include "hello.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(Hello) {
    emscripten::class_<HelloClass>("HelloClass")
        .constructor<>()
        .class_function("SayHello", &HelloClass::SayHello)
        .function("is64BitCompiled", &HelloClass::is64BitCompiled);
}
