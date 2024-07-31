#include <string>

class HelloClass {
public:
    static std::string SayHello(const std::string &name);
    bool is64BitCompiled();
private:
  static_assert(sizeof(size_t) == (64 / 8), "We require a 64-bit size_t");
};
