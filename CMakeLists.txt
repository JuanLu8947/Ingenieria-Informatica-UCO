add_library(computer computer.h)
target_link_libraries(computer PUBLIC product)
target_include_directories(computer PUBLIC ${CMAKE_CURRENT_LIST_DIR})
 
add_executable(computer-main computer-main.cc)
target_link_libraries(computer-main PUBLIC computer)