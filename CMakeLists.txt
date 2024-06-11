add_library(market market.cc market.h)
target_link_libraries(market PUBLIC product)
target_link_libraries(market PUBLIC client)
target_link_libraries(market PUBLIC seller)
target_include_directories(market PUBLIC ${CMAKE_CURRENT_LIST_DIR})
 
add_executable(market-main market-main.cc)
target_link_libraries(market-main PUBLIC market)