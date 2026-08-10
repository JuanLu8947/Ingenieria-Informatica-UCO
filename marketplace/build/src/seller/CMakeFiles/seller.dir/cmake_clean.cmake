file(REMOVE_RECURSE
  "libseller.a"
  "libseller.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/seller.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
