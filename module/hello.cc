#include "hello.h"

std::string HelloClass::SayHello(const std::string &name) {
    return "Yo! " + name;
}

bool HelloClass::is64BitCompiled() {
    return sizeof(size_t) == (64 / 8);
}
