cmake_minimum_required(VERSION 3.0.0)
project(Numpp VERSION 0.0 LANGUAGES CXX)
set(debug ON)
set(definitions cmake_MAJOR=${PROJECT_VERSION_MAJOR} cmake_MINOR=${PROJECT_VERSION_MINOR} cmake_NAME="${progname}")
set(coptions -pipe -O2 -Werror)
set(utilities utility vector differential)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  list(APPEND coptions -Weverything -fno-common --std=c++17 -Wno-c++98-compat -Wno-zero-as-null-pointer-constant -Wno-vla-extension -Wno-vla -Wno-covered-switch-default -Wno-padded -Wno-float-equal)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  list(APPEND coptions -Wall -W -Wconversion -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -fno-common --std=gnu++17)
else(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  message(SEND_ERROR "Unsupported compiler")
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

if(debug)
  list(APPEND definitions ___debug)  
  list(APPEND coptions -ggdb3)  
endif(debug)

if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
  add_definitions(${definitions})
else()
  add_compile_definitions(${definitions})
endif()
add_compile_options(${coptions})

message("Compile definitions ${definitions}")
message("Compile options ${coptions}")

include("default_buildinstall.cmake")

set(incdir "")
foreach(loopvar IN LISTS utilities)
  list(APPEND incdir ${CMAKE_CURRENT_SOURCE_DIR}/${loopvar})
endforeach(loopvar)
foreach(loopvar IN LISTS utilities)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${loopvar})
endforeach(loopvar)

install(FILES "LICENSE" DESTINATION "$ENV{PREFIX}/var/lib/${project}" PERMISSIONS WORLD_READ)
