set(sources vector.cpp)
set(linklibs " ")
set(properties " ")

# make each list a single argument
foreach(varn IN LISTS "sources;linklibs;properties")
  listtoarg(${${varn}} ${${varn}_l})
endforeach(varn)

defBI(sources_l "SHARED" linklibs_l properties_l ON)
