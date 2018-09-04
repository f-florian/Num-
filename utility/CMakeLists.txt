set(sources "except.cpp")
set(linklibs " ")
set(properties " ")
set(targets " ")

# make each list a single argument
foreach(varn IN LISTS "sources;linklibs;properties;targets")
  listtoarg(${${varn}} ${${varn}_l})
endforeach(varn)

defBI(sources_l "SHARED" linklibs_l targets_l properties_l OFF)
