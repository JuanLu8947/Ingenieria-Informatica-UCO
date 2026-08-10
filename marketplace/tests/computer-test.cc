// computer_tesc.cc: Juan A. Romero
// A sample program demonstrating using Google C++ testing framework.
//
// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good Idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include <computer.h>
#include "gtest/gtest.h"

TEST(Computer, ConstructorDefaultParam) {
  Computer c("33XX", ComputerType::Desktop, "empty", 0.0, "empty", "empty");
  
  EXPECT_EQ("33XX", c.GetId());
  EXPECT_EQ(ComputerType::Desktop, c.GetType());
  EXPECT_EQ("empty", c.GetName());
  EXPECT_NEAR(0.0, c.GetPrice(), 0.001);
  EXPECT_EQ("empty", c.GetMaker());
  EXPECT_EQ("empty", c.GetSeller());
}


TEST(Computer, ConstructorParam) {
  Computer c("44XX", ComputerType::Tablet, "Sun Computer 100X1", 1244.55, 
            "Distribuciones A", "Distribuciones B");
  
  EXPECT_EQ("44XX", c.GetId());
  EXPECT_EQ(ComputerType::Tablet, c.GetType());
  EXPECT_EQ("Sun Computer 100X1", c.GetName());
  EXPECT_NEAR(1244.55, c.GetPrice(), 0.001);
  EXPECT_EQ("Distribuciones A", c.GetMaker());
  EXPECT_EQ("Distribuciones B", c.GetSeller());
}

TEST(Computer, ComputerSetters) {
  Computer c("44XX", ComputerType::Tablet, "Sun Computer 100X1", 1244.55, 
            "Distribuciones A", "Distribuciones B");

  c.SetId("XX1");
  EXPECT_EQ("XX1", c.GetId());
  c.SetPrice(88.99);
  EXPECT_NEAR(88.99, c.GetPrice(), 0.001);
  c.SetMaker("Maker 1");
  EXPECT_EQ("Maker 1", c.GetMaker());
  c.SetSeller("Seller 1");
  EXPECT_EQ("Seller 1", c.GetSeller());
  c.SetType(ComputerType::Gaming);
  EXPECT_EQ(ComputerType::Gaming, c.GetType());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}