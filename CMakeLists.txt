cmake_minimum_required(VERSION 3.0.0)
# set project name and version
project(Numpp VERSION 0.0 LANGUAGES CXX)
# turn on debug settings
set(debug ON)
# pass version and name to the program as preprocessor definitions
set(definitions cmake_MAJOR=${PROJECT_VERSION_MAJOR} cmake_MINOR=${PROJECT_VERSION_MINOR} cmake_NAME="${progname}")
# set compile options
set(coptions -pipe -O2 -Werror)
# set subdirectories to add
# set(utilities subdirectory_1  ... subdirectory_n)
set(utilities utility vector differential permutation)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set complete compile flags depending on the compiler
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  list(APPEND coptions -Weverything -fno-common --std=c++17 -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-zero-as-null-pointer-constant -Wno-vla-extension -Wno-vla -Wno-covered-switch-default -Wno-padded -Wno-float-equal -fcomment-block-commands=file)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  list(APPEND coptions -Wall -W -Wconversion -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -fno-common --std=gnu++17)
else(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  message(SEND_ERROR "Unsupported compiler")
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

# set other compile flags ond definitions of debug is enabled
if(debug)
  list(APPEND definitions ___debug)  
  list(APPEND coptions -ggdb3)  
endif(debug)

# pass definitions to the compiler depending on CMake version
if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
  add_definitions(${definitions})
else()
  add_compile_definitions(${definitions})
endif()
add_compile_options(${coptions})

# output some info
# message("Compile definitions ${definitions}")
# message("Compile options ${coptions}")

# include module
include("CMakeSystem/buildinstall.cmake")

# add subdirectories to include directories (variable incdir is used in function defBI)
set(incdir "")
foreach(loopvar IN LISTS utilities)
  list(APPEND incdir ${CMAKE_CURRENT_SOURCE_DIR}/${loopvar})
endforeach(loopvar)

# add subbbdirectories
foreach(loopvar IN LISTS utilities)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${loopvar})
endforeach(loopvar)

# install license
install(FILES "LICENSE" DESTINATION "$ENV{PREFIX}/var/lib/${project}" PERMISSIONS WORLD_READ)
