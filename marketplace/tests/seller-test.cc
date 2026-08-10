// seller_test.cc: Juan A. Romero
// Testing Seller class

#include "gtest/gtest.h"
#include "seller.h"

TEST(Seller, ConstructorDefaultParam) {
  Seller p("33XX");
  
  EXPECT_EQ("33XX", p.GetId());
  EXPECT_EQ("empty", p.GetName());
  EXPECT_EQ("empty", p.GetTown());
  EXPECT_EQ("empty", p.GetProvince());
  EXPECT_EQ("empty", p.GetCountry());
  EXPECT_EQ(0, p.GetAge());
  EXPECT_FLOAT_EQ(0, p.GetRank());
  EXPECT_EQ(0, p.GetEntryYear());
  EXPECT_EQ("empty", p.GetSector());
}

TEST(Seller, ConstructorParam) {
  Seller p("44XX", "Carlos", "Córdoba", 
           "Córdoba", "España", 50, 1.7, 2023, "Motor");
  
  EXPECT_EQ("44XX", p.GetId());
  EXPECT_EQ("Carlos", p.GetName());
  EXPECT_EQ("Córdoba", p.GetTown());
  EXPECT_EQ("Córdoba", p.GetProvince());
  EXPECT_EQ("España", p.GetCountry());
  EXPECT_EQ(50, p.GetAge());
  EXPECT_FLOAT_EQ(1.7, p.GetRank());  
  EXPECT_EQ(2023, p.GetEntryYear());
  EXPECT_EQ("Motor", p.GetSector());
}


TEST(Seller, DefaultCopyConstructor) {
  Seller p("44XX", "Carlos", "Córdoba", 
           "Córdoba", "España", 50, 1.7, 2023, "Motor");
  Seller q(p);
  Seller r=q;
  EXPECT_EQ("44XX", q.GetId());
  EXPECT_EQ("Carlos", q.GetName());
  EXPECT_EQ("Córdoba", q.GetTown());
  EXPECT_EQ("Córdoba", q.GetProvince());
  EXPECT_EQ("España", q.GetCountry());
  EXPECT_EQ(50, q.GetAge());
  EXPECT_FLOAT_EQ(1.7, q.GetRank());  
  EXPECT_EQ(2023, q.GetEntryYear());
  EXPECT_EQ("Motor", q.GetSector());
  
  EXPECT_EQ("44XX", r.GetId());
  EXPECT_EQ("Carlos", r.GetName());
  EXPECT_EQ("Córdoba", r.GetTown());
  EXPECT_EQ("Córdoba", r.GetProvince());
  EXPECT_EQ("España", r.GetCountry());
  EXPECT_EQ(50, r.GetAge());
  EXPECT_FLOAT_EQ(1.7, r.GetRank());  
  EXPECT_EQ(2023, r.GetEntryYear());
  EXPECT_EQ("Motor", r.GetSector());
}

TEST(Seller, DefaultEqualOperator) {
  Seller p("44XX", "Carlos", "Córdoba", 
           "Córdoba", "España", 50, 1.7, 2023, "Motor");
  Seller q("66FF");
  q=p;
  EXPECT_EQ("44XX", q.GetId());
  EXPECT_EQ("Carlos", q.GetName());
  EXPECT_EQ("Córdoba", q.GetTown());
  EXPECT_EQ("Córdoba", q.GetProvince());
  EXPECT_EQ("España", q.GetCountry());
  EXPECT_EQ(50, q.GetAge());
  EXPECT_FLOAT_EQ(1.7, q.GetRank());  
  EXPECT_EQ(2023, q.GetEntryYear());
  EXPECT_EQ("Motor", q.GetSector());
}

TEST(Seller, Sector) {
  Seller p("44XX", "Carlos", "Córdoba", 
           "Córdoba", "España", 50, 1.7, 2023, "Electronics");
  EXPECT_EQ("Electronics",p.GetSector());
  Seller q("66FF");
  EXPECT_EQ("empty",q.GetSector());
  q.SetSector("Computers");
  EXPECT_EQ("Computers",q.GetSector());
  q.SetSector("Books");
  EXPECT_EQ("Books",q.GetSector());
  p.SetSector("Books");
  EXPECT_EQ("Books",q.GetSector());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}