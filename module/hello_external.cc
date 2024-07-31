#include "hello.h"
#include <fmt/core.h>

std::string HelloClass::SayHello(const std::string &name) {
    fmt::print("Sneaky Hello Message!\n");
    return "Yo! " + name;
}
