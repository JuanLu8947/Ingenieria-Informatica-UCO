add_library(person person.cc person.h)
target_include_directories(person PUBLIC ${CMAKE_CURRENT_LIST_DIR})
 
add_executable(person-main person-main.cc)
target_link_libraries(person-main PUBLIC person)