# GTest include code for fetch content over the internet 
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main gmock_main)
# End GTest include code

# Testing person library
add_executable(person-test person-test.cc)
target_link_libraries(person-test
 PRIVATE GTest::GTest person)
add_test(person-gtests person-test)

# Testing product library
add_executable(product-test product-test.cc)
target_link_libraries(product-test
 PRIVATE GTest::GTest product)
add_test(product_gtests product-test)

# Testing tv library
add_executable(tv-test tv-test.cc)
target_link_libraries(tv-test
 PRIVATE GTest::GTest tv)
add_test(tv_gtests tv-test)

# Testing computer library
add_executable(computer-test computer-test.cc)
target_link_libraries(computer-test
 PRIVATE GTest::GTest computer)
add_test(computer_gtests computer-test)

# Testing basket library
add_executable(basket-test basket-test.cc)
target_link_libraries(basket-test
 PRIVATE GTest::GTest basket product tv computer)
add_test(basket_gtests basket-test)

# Testing client library
add_executable(client-test client-test.cc)
target_link_libraries(client-test
 PRIVATE GTest::GTest client product basket)
add_test(client_gtests client-test)

# Testing seller library
add_executable(seller-test seller-test.cc)
target_link_libraries(seller-test
 PRIVATE GTest::GTest seller product basket)
add_test(seller_gtests seller-test)

# Testing market library
add_executable(market-test market-test.cc)
target_link_libraries(market-test
 PRIVATE GTest::GTest market product client seller)
add_test(market_gtests market-test)