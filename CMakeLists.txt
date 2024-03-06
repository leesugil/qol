
cmake_minimum_required(VERSION 3.10)
project(qol)

# Specify the C standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(include)

# Source files
# file(GLOB C_SOURCES "src/c/*.c")
add_library(qol SHARED ${C_SOURCES})

# Install the library
install(TARGETS qol DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
