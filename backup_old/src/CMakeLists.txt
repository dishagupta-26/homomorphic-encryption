# This command creates a library. A library is a collection of compiled code
# that can be used by other programs (like our example program later).
#
# We are naming our library "fhe_core".
# It is a STATIC library, which means its code gets copied directly into the
# final program that uses it. This is simpler for our project.
add_library(fhe_core STATIC
    # List of all the source (.cpp) files that are part of this library:
    math/polynomial.cpp
    math/ntt.cpp
    scheme/keygenerator.cpp
    scheme/encryptor.cpp
    scheme/decryptor.cpp
    scheme/evaluator.cpp
    api/context.cpp
)

# This command tells the compiler where to find the header (.h) files
# needed to compile our library and any program that uses it.
# We are making the entire 'src' directory available for includes.
# This means that in our code, we can write #include "math/polynomial.h"
target_include_directories(fhe_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# A message to confirm this file was processed.
message(STATUS "src/CMakeLists.txt processed, 'fhe_core' library target created.")