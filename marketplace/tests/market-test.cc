// market_test.cc: Juan A. Romero
// Testing class Market

#include "gtest/gtest.h"
#include <market.h>

TEST(Basket, Constructor) {
  Market m("Sell it again, Sam!");
  EXPECT_EQ("Sell it again, Sam!", m.GetSlogan());
}

TEST(Basket, GetSlogan) {
  Market m("Sell it");
  EXPECT_EQ("Sell it", m.GetSlogan());
}

TEST(Basket, SetSlogan) {
  Market m("Sell it");
  EXPECT_EQ("Sell it", m.GetSlogan());
  m.SetSlogan("");
  EXPECT_EQ("", m.GetSlogan());
  m.SetSlogan("Yes");
  EXPECT_EQ("Yes", m.GetSlogan());
}

TEST(Basket, AddClient) {
  Market m("Sell it!");
  EXPECT_EQ(0, m.NClients());
  Client c1("C1"), c2("C2");
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_EQ(1, m.NClients());
  EXPECT_TRUE(m.AddClient(c2));
  EXPECT_EQ(2, m.NClients());
  EXPECT_FALSE(m.AddClient(c2));
  EXPECT_FALSE(m.AddClient(c1));
}

TEST(Basket, AddSeller) {
  Market m("Sell it");
  EXPECT_EQ(0, m.NSellers());
  Seller s1("S1"), s2("S2");
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_EQ(1, m.NSellers());
  EXPECT_TRUE(m.AddSeller(s2));
  EXPECT_EQ(2, m.NSellers());
  EXPECT_FALSE(m.AddSeller(s2));
  EXPECT_FALSE(m.AddSeller(s1));
}

TEST(Basket, DeleteClient) {
  Market m("Sell it");
  EXPECT_EQ(0, m.NClients());
  Client c1("C1"), c2("C2");
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_EQ(1, m.NClients());
  EXPECT_TRUE(m.AddClient(c2));
  EXPECT_EQ(2, m.NClients());
  EXPECT_TRUE(m.DeleteClient(c2));
  EXPECT_EQ(1, m.NClients());
  EXPECT_TRUE(m.DeleteClient(c1));
  EXPECT_EQ(0, m.NClients());
  EXPECT_FALSE(m.DeleteClient(c1));
  EXPECT_FALSE(m.DeleteClient(c2));
}

TEST(Basket, DeleteSeller) {
  Market m("Sell it");
  EXPECT_EQ(0, m.NSellers());
  Seller s1("S1"), s2("S2");
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_EQ(1, m.NSellers());
  EXPECT_TRUE(m.AddSeller(s2));
  EXPECT_EQ(2, m.NSellers());
  EXPECT_TRUE(m.DeleteSeller(s1));
  EXPECT_EQ(1, m.NSellers());
  EXPECT_TRUE(m.DeleteSeller(s2));
  EXPECT_EQ(0, m.NSellers());
  EXPECT_FALSE(m.DeleteSeller(s1));
  EXPECT_FALSE(m.DeleteSeller(s2));
}

TEST(Basket, DeletingAddingClientsAndSellers) {
  Market m("Sell it");
  EXPECT_EQ(0, m.NClients());
  EXPECT_EQ(0, m.NSellers());
  Seller s1("S1"), s2("S2");
  Client c1("C1"), c2("C2"), c3("C3");
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_EQ(1, m.NClients());
  EXPECT_EQ(1, m.NSellers());
  EXPECT_TRUE(m.DeleteSeller(s1));
  EXPECT_EQ(1, m.NClients());
  EXPECT_EQ(0, m.NSellers());
  EXPECT_TRUE(m.AddClient(c2));
  EXPECT_EQ(2, m.NClients());
  EXPECT_EQ(0, m.NSellers());
  EXPECT_FALSE(m.DeleteSeller(s1));
  EXPECT_FALSE(m.DeleteSeller(s2));
  EXPECT_FALSE(m.DeleteClient(c3));
}

TEST(Basket, AddProductSeller) {
  Market m("Sell it");
  Seller s1("S1"), s2("S2");
  Client c1("C1"), c2("C2");
  Product p1("P1", "tv", 2345.9);
  Product p2("P2", "PC", 1378.5);
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_TRUE(m.AddSeller(s2));
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_TRUE(m.AddClient(c2));
  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p2, "S1"));
  EXPECT_FALSE(m.AddProductSeller(p2, "XX"));
}

TEST(Basket, AddProductClient) {
  Market m("Sell it");
  Seller s1("S1"), s2("S2");
  Client c1("C1"), c2("C2");
  Product p1("P1", "tv", 2345.9);
  Product p2("P2", "PC", 1378.5);
  Product p3("P3", "Laptop", 1378.5);
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_TRUE(m.AddSeller(s2));
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_TRUE(m.AddClient(c2));
  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p2, "S1"));
  EXPECT_TRUE(m.AddProductClient(p1, "C1"));
  EXPECT_TRUE(m.AddProductClient(p2, "C1"));
  EXPECT_FALSE(m.AddProductClient(p2, "XX")); // client doesn't exists
  EXPECT_FALSE(m.AddProductClient(p3, "C1")); // product not on sale
}

TEST(Basket, DeleteProductSeller) {
  Market m("Sell it");
  Seller s1("S1"), s2("S2");
  Client c1("C1"), c2("C2");
  Product p1("P1", "tv", 10);
  Product p2("P2", "PC", 20);
  Product p3("P3", "Laptop", 30);
  Product p4("P4", "Tv", 40);
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_TRUE(m.AddSeller(s2));
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_TRUE(m.AddClient(c2));

  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p2, "S1"));

  EXPECT_TRUE(m.AddProductSeller(p3, "S2"));
  
  EXPECT_TRUE(m.DeleteProductSeller(p1, "S1"));
  EXPECT_FALSE(m.DeleteProductSeller(p3, "S1"));
  EXPECT_FALSE(m.DeleteProductSeller(p4, "S1"));

  EXPECT_TRUE(m.DeleteProductSeller(p3, "S2"));
  EXPECT_FALSE(m.DeleteProductSeller(p3, "S2"));
}

TEST(Basket, DeleteProductClient) {
  Market m("Sell it");
  Seller s1("S1"), s2("S2");
  Client c1("C1"), c2("C2");
  Product p1("P1", "tv", 10);
  Product p2("P2", "PC", 20);
  Product p3("P3", "Laptop", 30);
  Product p4("P4", "Tv", 40);
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_TRUE(m.AddSeller(s2));
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_TRUE(m.AddClient(c2));

  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p2, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p3, "S2"));
  
  EXPECT_TRUE(m.AddProductClient(p1, "C1"));
  EXPECT_TRUE(m.AddProductClient(p2, "C1"));
  EXPECT_TRUE(m.AddProductClient(p3, "C1"));

  EXPECT_FALSE(m.DeleteProductSeller(p4, "S1"));
  EXPECT_FALSE(m.DeleteProductClient(p4, "C1"));

  EXPECT_NEAR(60.0, m.GetMoneyInBasket(), 0.1);
  EXPECT_TRUE(m.DeleteProductClient(p3, "C1"));
  EXPECT_NEAR(30.0, m.GetMoneyInBasket(), 0.1);

  EXPECT_TRUE(m.DeleteProductClient(p2, "C1"));
  EXPECT_NEAR(10.0, m.GetMoneyInBasket(), 0.1);

  EXPECT_FALSE(m.AddProductClient(p2, "C1"));
  EXPECT_NEAR(10.0, m.GetMoneyInBasket(), 0.1);
}

TEST(Basket, GetMoneyInBasket) {
  Market m("Sell it");
  Seller s1("S1"), s2("S2");
  Client c1("C1"), c2("C2");
  Product p1("P1", "tv", 10);
  Product p2("P2", "PC", 20);
  Product p3("P3", "Laptop", 30);
  Product p4("P4", "Laptop", 5);
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_TRUE(m.AddSeller(s2));
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_TRUE(m.AddClient(c2));

  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p2, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p2, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p3, "S1"));

  EXPECT_TRUE(m.AddProductSeller(p4, "S2"));
  
  EXPECT_TRUE(m.AddProductClient(p1, "C1"));
  EXPECT_TRUE(m.AddProductClient(p2, "C1"));
  EXPECT_TRUE(m.AddProductClient(p3, "C1"));
  EXPECT_NEAR(60.0, m.GetMoneyInBasket(), 0.1);

  EXPECT_TRUE(m.AddProductClient(p1, "C1"));
  EXPECT_NEAR(70.0, m.GetMoneyInBasket(), 0.1);

  EXPECT_FALSE(m.AddProductClient(p1, "C1"));
  EXPECT_NEAR(70.0, m.GetMoneyInBasket(), 0.1);

  EXPECT_FALSE(m.AddProductClient(p1, "C2"));
  EXPECT_NEAR(70.0, m.GetMoneyInBasket(), 0.1);

  EXPECT_TRUE(m.AddProductClient(p4, "C2"));
  EXPECT_NEAR(75.0, m.GetMoneyInBasket(), 0.1);

  EXPECT_TRUE(m.AddProductClient(p2, "C2"));
  EXPECT_NEAR(95.0, m.GetMoneyInBasket(), 0.1);

  EXPECT_FALSE(m.AddProductClient(p1, "C2"));
  EXPECT_NEAR(95.0, m.GetMoneyInBasket(), 0.1);
}

TEST(Basket, DumpMarket) {
  Market m("Sell it");
  Seller s1("S1"), s2("S2");
  Client c1("C1"), c2("C2");
  Product p1("P1", "tv", 10);
  Product p2("P2", "PC", 20);
  Product p3("P3", "Laptop", 30);
  Product p4("P4", "Laptop", 5);
  Product p5("P5", "Laptop", 15);
  EXPECT_TRUE(m.AddSeller(s1));
  EXPECT_TRUE(m.AddSeller(s2));
  EXPECT_TRUE(m.AddClient(c1));
  EXPECT_TRUE(m.AddClient(c2));

  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p1, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p2, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p2, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p3, "S1"));
  EXPECT_TRUE(m.AddProductSeller(p4, "S2"));
  EXPECT_TRUE(m.AddProductSeller(p4, "S2"));
  EXPECT_TRUE(m.AddProductSeller(p5, "S2"));

  
  EXPECT_TRUE(m.AddProductClient(p1, "C1"));
  EXPECT_TRUE(m.AddProductClient(p2, "C1"));
  EXPECT_TRUE(m.AddProductClient(p2, "C1"));
  EXPECT_TRUE(m.AddProductClient(p3, "C1"));

  EXPECT_TRUE(m.AddProductClient(p5, "C2"));
  EXPECT_TRUE(m.AddProductClient(p1, "C2"));
  EXPECT_TRUE(m.AddProductClient(p4, "C2"));
  
  EXPECT_TRUE(m.DumpMarket(1));
  EXPECT_TRUE(m.DumpMarket(0));
  EXPECT_FALSE(m.DumpMarket(10));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}