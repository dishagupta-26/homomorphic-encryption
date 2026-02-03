add_executable(run_demo
    linear_regression.cpp
)

# FIX: Tell this target where to find the header files from our library.
# The variable ${CMAKE_SOURCE_DIR} points to the top-level project folder (fhe-framework).
target_include_directories(run_demo PRIVATE ${CMAKE_SOURCE_DIR}/src)

# This is the "linking" command we already had.
# It connects the compiled code of the library to our program.
target_link_libraries(run_demo PRIVATE fhe_core)

message(STATUS "examples/CMakeLists.txt processed, 'run_demo' executable target created.")