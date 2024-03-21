
cmake_minimum_required(VERSION 3.10)
project(qol)

# Specify the C standard
#set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Include directories
include_directories(include)

# Source files
file(GLOB C_SOURCES "src/c/*.c")
file(GLOB CPP_SOURCES "src/cpp/*.cpp")
add_library(qol SHARED ${C_SOURCES} ${CPP_SOURCES})

# Install the library
install(TARGETS qol DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# CPack Packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_GENERATOR "TGZ;ZIP")
include(CPack)
