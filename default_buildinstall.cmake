function(listtoarg list_v arg_v)
  string(REPLACE ";" "\;" arg_v ${list_v})
endfunction(listtoarg)

function(argtolist arg_v list_v)
  string(REPLACE "\;" ";" list_v ${arg_v})
endfunction(argtolist)


function(defBI sources_l type linklibs_l properties_l install)
  # make arguments lists again
  foreach(varn IN LISTS "sources;linklibs;properties")
    argtolist(${${varn}_l} ${${varn}})
  endforeach(varn)

  # get a name for the current target, based on the current directory  
  string(REPLACE "${CMAKE_SOURCE_DIR}/" "" progname_tmp ${CMAKE_CURRENT_SOURCE_DIR})
  string(REPLACE "/" "_" progname ${progname_tmp})

  if(${type} STREQUAL "EXECUTABLE")
    message("adding program \"${progname}\"")
    add_executable(${progname} ${sources})
    set(type_v "RUNTIME")
    set(destination_v "$ENV{PREFIX}/bin")
  elseif(${type} STREQUAL "SHARED")
    message("adding library \"${progname}\"")
    add_library(${progname} SHARED ${sources})
    set(type_v "LIBRARY")
    set(destination_v "$ENV{PREFIX}/lib")
  else()
    message("Target \"${progname}\" won't build anything")
    return()
  endif()

  foreach(loopvar IN LISTS properties)
    set_property(TARGET ${progname} PROPERTY ${loopvar})
  endforeach(loopvar)
  foreach(loopvar IN LISTS linklibs)
    string(REPLACE "_" "/" linklibs_d ${loopvar})
    if(${loopvar} STREQUAL " ")
      return()
    endif()
    find_library(libloc${loopvar} ${loopvar} PATHS "${CMAKE_BINARY_DIR}/${linklibs_d}")
    message("${progname} links to ${loopvar}, searching in ${CMAKE_BINARY_DIR}/${linklibs_d}, found in ${libloc${loopvar}}")
    target_link_libraries(${progname} ${libloc})
  endforeach(loopvar)

  message("${INCLUDE_DIRECTORIES}")
  message("${SYSTEM_INCLUDE_DIRECTORIES}")
  message("${CMAKE_INCLUDE_DIRECTORIES}")
  
  if(${install} MATCHES "NO.*" OR ${install} STREQUAL "OFF")
    message("Target \"${progname}\" won't install anything")
  elseif(${install} STREQUAL "ON" OR ${install} STREQUAL "INSTALL")
    install(TARGETS ${progname} ${type_v} DESTINATION ${destination_v})
  else(${install} MATCHES "NO.*" OR ${install} STREQUAL "OFF")
    message("Cannot parse \"INSTALL\" argument. Target \"${progname}\" won't install anything")
  endif(${install} MATCHES "NO.*" OR ${install} STREQUAL "OFF")
endfunction(defBI)
