cmake_minimum_required(VERSION 3.5)

project(CppCon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DUseVirtual)

file(GLOB Sources *.h *cpp)

add_executable(CppCon ${Sources})

install(TARGETS CppCon
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
