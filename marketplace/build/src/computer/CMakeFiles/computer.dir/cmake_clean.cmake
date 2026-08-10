file(REMOVE_RECURSE
  "libcomputer.a"
  "libcomputer.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/computer.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
