# -*- mode: cmake; eval: (hl-line-mode 0);-*-
cmake_minimum_required(VERSION 3.0.0)
project(Numpp VERSION 0.0 LANGUAGES CXX)
(set debug ON)
(set definitions -Dcmake_MAJOR=${PROJECT_VERSION_MAJOR} -Dcmake_MINOR=${PROJECT_VERSION_MINOR} -Dcmake_NAME="${progname}")
(set coptions -O2)


if(CMAKE_<LANG>_COMPILER_ID STREQUAL "Clang")
  list(APPEND coptions -pipe -Werror -Weverything -fno-common --std=gnu++17)
elseif(CMAKE_<LANG>_COMPILER_ID STREQUAL "GNU")
  list(APPEND coptions -pipe -Werror -Wall -W -Wconversion -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -fno-common --std=gnu++17)
else(CMAKE_<LANG>_COMPILER_ID STREQUAL "Clang")
  message(SEND_ERROR "message to displayUnsupported compiler")
endif(CMAKE_<LANG>_COMPILER_ID STREQUAL "Clang")

if(debug)
  list(APPEND definitions -D___debug)  
  list(APPEND coptions -ggdb3)  
endif(debug)

add_compile_definitions(definitions)
add_compile_options(coptions)

set(progname ${PROJECT_NAME})

add_library(${progname} SHARED ${sources})
install(TARGETS ${progname} LIBRARY DESTINATION "$ENV{PREFIX}/lib" PERMISSIONS WORLD_READ)
install(FILES "differential.h" DESTINATION "$ENV{PREFIX}/include" PERMISSIONS WORLD_READ)
install(FILES "LICENSE" DESTINATION "$ENV{PREFIX}/var/lib/${progname}" PERMISSIONS WORLD_READ)
