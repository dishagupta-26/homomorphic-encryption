#include <iostream>
#include "math/mod_arith.h"

int main() {
    int64_t q = 7;
    std::cout << fhe::mod(-3, q) << std::endl;  // should print 4
}
