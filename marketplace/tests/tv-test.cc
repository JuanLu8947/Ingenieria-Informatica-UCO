// tv_test.cc: Juan A. Romero
// A sample program demonstrating using Google C++ testing framework.
//
// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include <tv.h>
#include "gtest/gtest.h"

TEST(Tv, ConstructorDefaultParam) {
  Tv t("33XX", "empty", 0.0, "empty", "empty", 0.0);
  
  EXPECT_EQ("33XX", t.GetId());
  EXPECT_EQ("empty", t.GetName());
  EXPECT_NEAR(0.0, t.GetPrice(), 0.001);
  EXPECT_EQ("empty", t.GetMaker());
  EXPECT_EQ("empty", t.GetSeller());
  EXPECT_NEAR(0.0, t.GetInch(), 0.001);
}

TEST(Tv, ConstructorParam) {
  Tv t("44XX", "Sun tv 100X1", 1244.55, 
            "Distribuciones A", "Distribuciones B",
            50);
  
  EXPECT_EQ("44XX", t.GetId());
  EXPECT_EQ("Sun tv 100X1", t.GetName());
  EXPECT_NEAR(1244.55, t.GetPrice(), 0.001);
  EXPECT_EQ("Distribuciones A", t.GetMaker());
  EXPECT_EQ("Distribuciones B", t.GetSeller());
  EXPECT_NEAR(50, t.GetInch(), 0.001);
}

TEST(Tv, TvSetters) {
  Tv t("44XX", "Tv", 44.55, 
            "Distribuciones A", "Distribuciones B", 0.0);

  t.SetId("XX1");
  EXPECT_EQ("XX1", t.GetId());
  t.SetPrice(88.99);
  EXPECT_NEAR(88.99, t.GetPrice(), 0.001);
  t.SetMaker("Maker 1");
  EXPECT_EQ("Maker 1", t.GetMaker());
  t.SetSeller("Seller 1");
  EXPECT_EQ("Seller 1", t.GetSeller());
  EXPECT_NEAR(0.0, t.GetInch(), 0.001);
  EXPECT_TRUE(t.SetInch(60.6));
  EXPECT_NEAR(60.6, t.GetInch(), 0.001);
}

TEST(Tv, Tv_set_Inch) {
  Tv t("44XX", "empty", 0.0, "empty", "empty", 0.0);    

  EXPECT_NEAR(0.0, t.GetInch(), 0.001);
  EXPECT_TRUE(t.SetInch(60.6));
  EXPECT_NEAR(60.6, t.GetInch(), 0.001);
  EXPECT_FALSE(t.SetInch(-100));
  EXPECT_NEAR(60.6, t.GetInch(), 0.001);
  EXPECT_FALSE(t.SetInch(0));
  EXPECT_NEAR(60.6, t.GetInch(), 0.001);  
  EXPECT_FALSE(t.SetInch(-0.001));
  EXPECT_NEAR(60.6, t.GetInch(), 0.001);  
  EXPECT_TRUE(t.SetInch(0.1));
  EXPECT_NEAR(0.1, t.GetInch(), 0.001);  
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}