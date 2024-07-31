#include <iostream>
#include "hello.h"

namespace {
int DoMain() {
    HelloClass hello;
    std::cout << hello.SayHello("Bob") << std::endl;
    return 0;
}

}  // namespace

int main() {
  return DoMain();
}