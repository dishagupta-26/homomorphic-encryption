# This command creates an executable program.
# We are naming the final program "run_demo".
# It will be built from our single example source file.
add_executable(run_demo
    linear_regression.cpp
)

# This is the most important part of this file.
# It "links" our executable program with our library.
# This means all the code from "fhe_core" will be available inside "run_demo".
target_link_libraries(run_demo PRIVATE fhe_core)

# A message to confirm this file was processed.
message(STATUS "examples/CMakeLists.txt processed, 'run_demo' executable target created.")