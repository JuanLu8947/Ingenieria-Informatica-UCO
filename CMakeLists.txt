add_library(product product.cc product.h)
target_include_directories(product PUBLIC ${CMAKE_CURRENT_LIST_DIR})
 
add_executable(product-main product-main.cc)
target_link_libraries(product-main PUBLIC product)