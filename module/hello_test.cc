#include <iostream>
#include "hello.h"

namespace {
int DoMain() {
    HelloClass hello;
    std::cout << "Is 64 bit compiled?: " << (hello.is64BitCompiled()? "yes":"no") << std::endl;
    return 0;
}

}  // namespace

int main() {
  return DoMain();
}