// client_test.cc: Juan A. Romero
// Testing Client class

#include "gtest/gtest.h"
#include "client.h"


TEST(Client, ConstructorDefaultParam) {
  Client p("33XX");
  
  EXPECT_EQ("33XX", p.GetId());
  EXPECT_EQ("empty", p.GetName());
  EXPECT_EQ("empty", p.GetTown());
  EXPECT_EQ("empty", p.GetProvince());
  EXPECT_EQ("empty", p.GetCountry());
  EXPECT_EQ(0, p.GetAge());
  EXPECT_FLOAT_EQ(0, p.GetRank());
  EXPECT_EQ(0, p.GetEntryYear());
  EXPECT_EQ(0, p.GetPremium());
}

TEST(Client, ConstructorParam) {
  Client p("44XX", "Carlos", "Córdoba", 
           "Córdoba", "España", 50, 1.7, 2023,3);
  
  EXPECT_EQ("44XX", p.GetId());
  EXPECT_EQ("Carlos", p.GetName());
  EXPECT_EQ("Córdoba", p.GetTown());
  EXPECT_EQ("Córdoba", p.GetProvince());
  EXPECT_EQ("España", p.GetCountry());
  EXPECT_EQ(50, p.GetAge());
  EXPECT_FLOAT_EQ(1.7, p.GetRank());  
  EXPECT_EQ(2023, p.GetEntryYear());
  EXPECT_EQ(3, p.GetPremium());
}

TEST(Client, DefaultCopyConstructor) {
  Client p("44XX", "Carlos", "Córdoba", 
           "Córdoba", "España", 50, 1.7, 2023,5);
  Client q(p);
  Client r=q;
  EXPECT_EQ("44XX", q.GetId());
  EXPECT_EQ("Carlos", q.GetName());
  EXPECT_EQ("Córdoba", q.GetTown());
  EXPECT_EQ("Córdoba", q.GetProvince());
  EXPECT_EQ("España", q.GetCountry());
  EXPECT_EQ(50, q.GetAge());
  EXPECT_FLOAT_EQ(1.7, q.GetRank());  
  EXPECT_EQ(2023, q.GetEntryYear());
  EXPECT_EQ(5, q.GetPremium());
  
  EXPECT_EQ("44XX", r.GetId());
  EXPECT_EQ("Carlos", r.GetName());
  EXPECT_EQ("Córdoba", r.GetTown());
  EXPECT_EQ("Córdoba", r.GetProvince());
  EXPECT_EQ("España", r.GetCountry());
  EXPECT_EQ(50, r.GetAge());
  EXPECT_FLOAT_EQ(1.7, r.GetRank());  
  EXPECT_EQ(2023, r.GetEntryYear());
  EXPECT_EQ(5, r.GetPremium());
}

TEST(Client, DefaultEqualOperator) {
  Client p("44XX", "Carlos", "Córdoba", 
           "Córdoba", "España", 50, 1.7, 2023,5);
  Client q("66FF");
  q=p;
  EXPECT_EQ("44XX", q.GetId());
  EXPECT_EQ("Carlos", q.GetName());
  EXPECT_EQ("Córdoba", q.GetTown());
  EXPECT_EQ("Córdoba", q.GetProvince());
  EXPECT_EQ("España", q.GetCountry());
  EXPECT_EQ(50, q.GetAge());
  EXPECT_FLOAT_EQ(1.7, q.GetRank());  
  EXPECT_EQ(2023, q.GetEntryYear());
  EXPECT_EQ(5, q.GetPremium());
}

TEST(Client, Premium) {
  Client p("44XX", "Carlos", "Córdoba", 
           "Córdoba", "España", 50, 1.7, 2023,5);
  EXPECT_EQ(5,p.GetPremium());
  Client q("66FF");
  EXPECT_EQ(0,q.GetPremium());
  q.SetPremium(1);
  EXPECT_EQ(1,q.GetPremium());
  q.SetPremium(6);
  EXPECT_EQ(6,q.GetPremium());
  p.SetPremium(6);
  EXPECT_EQ(6,q.GetPremium());
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}