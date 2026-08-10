add_library(basket basket.cc basket.h)
target_link_libraries(basket PUBLIC product)
target_link_libraries(basket PUBLIC computer)
target_link_libraries(basket PUBLIC tv)
target_include_directories(basket PUBLIC ${CMAKE_CURRENT_LIST_DIR})
 
add_executable(basket-main basket-main.cc)
target_link_libraries(basket-main PUBLIC basket)