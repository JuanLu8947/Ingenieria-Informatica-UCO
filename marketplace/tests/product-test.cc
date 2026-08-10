// product_test.cc: Juan A. Romero
// A sample program demonstrating using Google C++ testing framework.
//
// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include <product.h>
#include "gtest/gtest.h"

TEST(Product, ConstructorDefaultParam) {
  Product p("33XX", "empty", 0.0, "empty", "empty");
  
  EXPECT_EQ("33XX", p.GetId());
  EXPECT_EQ("empty", p.GetName());
  EXPECT_NEAR(0.0, p.GetPrice(), 0.001);
  EXPECT_EQ("empty", p.GetMaker());
  EXPECT_EQ("empty", p.GetSeller());
}

TEST(Product, ConstructorParam) {
  Product p("44XX", "Tv", 44.55, 
            "Distribuciones A", "Distribuciones B");
  
  EXPECT_EQ("44XX", p.GetId());
  EXPECT_EQ("Tv", p.GetName());
  EXPECT_NEAR(44.55, p.GetPrice(), 0.001);
  EXPECT_EQ("Distribuciones A", p.GetMaker());
  EXPECT_EQ("Distribuciones B", p.GetSeller());
}

TEST(Product, ProductSetters) {
  Product p("44XX", "Tv", 44.55, 
            "Distribuciones A", "Distribuciones B");    

  p.SetId("XX1");
  EXPECT_EQ("XX1", p.GetId());
  p.SetPrice(88.99);
  EXPECT_NEAR(88.99, p.GetPrice(), 0.001);
  p.SetMaker("Maker 1");
  EXPECT_EQ("Maker 1", p.GetMaker());
  p.SetSeller("Seller 1");
  EXPECT_EQ("Seller 1", p.GetSeller());
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}