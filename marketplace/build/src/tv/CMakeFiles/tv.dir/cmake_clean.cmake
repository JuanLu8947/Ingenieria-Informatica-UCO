file(REMOVE_RECURSE
  "libtv.a"
  "libtv.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/tv.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
