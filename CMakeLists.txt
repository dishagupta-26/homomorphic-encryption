# Specifies the minimum version of CMake required to build this project.
cmake_minimum_required(VERSION 3.15)

# Defines our project's name, version, and programming language (C++).
project(
    FHE_Framework
    VERSION 1.0
    LANGUAGES CXX
)

# Set the C++ standard we want to use. C++17 is a good, modern choice.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tell CMake to look inside the 'src' directory for more source files
# and another CMakeLists.txt file.
add_subdirectory(src)

# Tell CMake to also look inside the 'examples' directory for our demo code
# and another CMakeLists.txt file.
add_subdirectory(examples)

# We will add the 'bindings' directory later when we tackle the Python part.

# A message to confirm this file was processed.
message(STATUS "Top-level CMakeLists.txt processed for FHE_Framework.")