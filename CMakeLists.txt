cmake_minimum_required(VERSION 3.10)
project(ESCA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

# set(CMAKE_VERBOSE_MAKEFILE TRUE)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")

add_compile_definitions(DEBUG)
add_compile_definitions(TEXT_DIAG)
#add_compile_definitions(SAVE_XML)
#add_compile_definitions(DEBUGOUT)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
#add_compile_options(-Wall -Wextra)

message(STATUS "Found LLVM: ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
# set(LLVM_LIBS ${LLVM_INCLUDE_DIRS}/../lib/*)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
# add_definitions(${LLVM_DEFINITIONS_LIST})

#add_definitions(${LLVM_DEFINITIONS})
#add_definitions(${CLANG_DEFINITIONS})

add_subdirectory(src)
add_subdirectory(tests)
# message(STATUS "LLVM_LIBRARIES: ${LLVM_LIBRARY_DIR}")
