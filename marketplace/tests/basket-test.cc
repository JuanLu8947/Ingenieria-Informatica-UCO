// basket_test.cc: Juan A. Romero
// Testing class Basket

#include "gtest/gtest.h"
#include "basket.h"
#include "product.h"
#include "tv.h"
#include "computer.h"


TEST(Basket, Basket_add_product) {
  Basket b;
  Product p1("11XX"), p2("22XX"), p3("33XX");
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  Product p4("44XX"), p5("55XX");
  b.AddProduct(p4);
  b.AddProduct(p5);
  EXPECT_EQ(5, b.GetSize());
}


TEST(Basket, Basket_delete_product1) {
  Basket b;
  Product p1("11XX"), p2("22XX"), p3("33XX");
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  EXPECT_EQ(3, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct(p1));
  EXPECT_EQ(2, b.GetSize());
  Product p4("44XX"), p5("55XX");
  b.AddProduct(p4);
  EXPECT_EQ(3, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct(p5));
  EXPECT_EQ(3, b.GetSize());
  b.AddProduct(p1);
  EXPECT_EQ(4, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct(p5));
  EXPECT_EQ(4, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct(p1));
  EXPECT_TRUE(b.DeleteProduct(p2));
  EXPECT_TRUE(b.DeleteProduct(p3));
  EXPECT_TRUE(b.DeleteProduct(p4));
  EXPECT_EQ(0, b.GetSize());
}

TEST(Basket, Basket_delete_product2) {
  Basket b;
  Product p1("11XX"), p2("22XX"), p3("33XX");
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  EXPECT_EQ(3, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct(p1.GetId()));
  EXPECT_EQ(2, b.GetSize());
  Product p4("44XX"), p5("55XX");
  b.AddProduct(p4);
  EXPECT_EQ(3, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct(p5.GetId()));
  EXPECT_EQ(3, b.GetSize());
  b.AddProduct(p1);
  EXPECT_EQ(4, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct(p5));
  EXPECT_EQ(4, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct(p1.GetId()));
  EXPECT_TRUE(b.DeleteProduct(p2.GetId()));
  EXPECT_TRUE(b.DeleteProduct(p3.GetId()));
  EXPECT_TRUE(b.DeleteProduct(p4.GetId()));
  EXPECT_EQ(0, b.GetSize());
}

TEST(Basket, Basket_delete_basket) {
  Basket b;
  Product p1("P1"), p2("P2"), p3("P3");
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  EXPECT_EQ(3, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct(p1.GetId()));
  EXPECT_EQ(2, b.GetSize());

  Product p4("P4"), p5("P5"), p6("P6");
  b.AddProduct(p4);
  EXPECT_EQ(3, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct(p5.GetId()));
  EXPECT_EQ(3, b.GetSize());

  b.AddProduct(p1); // p1 lo había borrado
  EXPECT_EQ(4, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct(p5));
  EXPECT_EQ(4, b.GetSize());

  b.DeleteBasket();
  EXPECT_EQ(0, b.GetSize());
  b.AddProduct(p1);
  EXPECT_EQ(1, b.GetSize());
  b.AddProduct(p2);
  EXPECT_EQ(2, b.GetSize());
  b.AddProduct(p3);
  EXPECT_EQ(3, b.GetSize());
  b.DeleteBasket();
  EXPECT_EQ(0, b.GetSize());  
}


TEST(Basket, ZeroProducts) {
  Basket b;
  EXPECT_EQ(0, b.GetSize());
}

TEST(Basket, AddProduct) {
  Basket b;
  Product p1("P1"), p2("P2"), p3("P3");
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  Product *p= new Product("XX1");
  b.AddProduct(*p);
  delete p;
  EXPECT_EQ(4, b.GetSize());
}

TEST(Basket, AddMoreProducts) {
  Basket b;
  Product p1("P1"), p2("P2"), p3("P3");
  Tv t1("Tv1");
  Computer c1("C1", ComputerType::Server);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  b.AddProduct(t1);
  b.AddProduct(c1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  Product *p= new Product("XX1");
  b.AddProduct(*p);
  delete p;
  EXPECT_EQ(6, b.GetSize());
}

TEST(Basket, DeleteProductsP) {
  Basket b;
  Product p1("P1"), p2("P2"), p3("P3");
  Tv t1("Tv1");
  Computer c1("C1", ComputerType::Server);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  b.AddProduct(t1);
  b.AddProduct(c1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  Product *p= new Product("XX1");
  b.AddProduct(*p);
  delete p;
  EXPECT_EQ(6, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct(p3)); // decrementa en 1 catidad de p3 (queda 1)
  EXPECT_EQ(6, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct(p3)); // Ahora p3 ya sale de la cesta
  EXPECT_EQ(5, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct(t1)); 
  EXPECT_EQ(4, b.GetSize());
}

TEST(Basket, DeleteProductsId) {
  Basket b;
  Product p1("P1"), p2("P2"), p3("P3");
  Tv t1("Tv1");
  Computer c1("C1", ComputerType::Server);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  b.AddProduct(t1);
  b.AddProduct(c1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  Product *p= new Product("XX1");
  b.AddProduct(*p);
  delete p;
  EXPECT_EQ(6, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct("P3")); // decrementa en 1 catidad de p3 (queda 1)
  EXPECT_EQ(6, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct("P3")); // Ahora p3 ya sale de la cesta
  EXPECT_EQ(5, b.GetSize());
  EXPECT_TRUE(b.DeleteProduct("Tv1")); 
  EXPECT_EQ(4, b.GetSize());
}

TEST(Basket, DeleteProductsNoId) {
  Basket b;
  Product p1("P1"), p2("P2"), p3("P3");
  b.AddProduct(p1);
  b.AddProduct(p2);
  EXPECT_EQ(2, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct(p3));
  EXPECT_EQ(2, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct("P5"));
  EXPECT_EQ(2, b.GetSize());
  EXPECT_FALSE(b.DeleteProduct("XX"));
  EXPECT_EQ(2, b.GetSize());  
  EXPECT_TRUE(b.DeleteProduct("P1"));
  EXPECT_EQ(1, b.GetSize());  
  EXPECT_TRUE(b.DeleteProduct("P2"));
  EXPECT_EQ(0, b.GetSize()); 
}

TEST(Basket, AddAndDeleteProducts) {
  Basket b;
  Product p1("P1"), p2("P2"), p3("P3");
  Tv t1("Tv1");
  Computer c1("C1", ComputerType::Server);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  EXPECT_EQ(3, b.GetSize());
  b.DeleteProduct(p3);
  EXPECT_EQ(2, b.GetSize());
  b.AddProduct(t1);
  b.AddProduct(c1);
  EXPECT_EQ(4, b.GetSize());
  b.DeleteProduct(t1);
  b.DeleteProduct(c1);
  EXPECT_EQ(2, b.GetSize());
  b.DeleteProduct(p1);
  b.DeleteProduct(p2);
  EXPECT_EQ(0, b.GetSize());
}

TEST(Basket, BasketTotalZero) {
  Basket b;
  Product p1("P1"), p2("P2"), p3("P3");
  EXPECT_FLOAT_EQ(0.0,b.GetTotal());
}

TEST(Basket, BasketTotal) {
  Basket b;
  Product p1("P1", "Product 1", 100.5);
  Product p2("P2", "Product 2", 200.5);
  Product p3("P3", "Product 3", 300.5);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  EXPECT_FLOAT_EQ(601.5,b.GetTotal());
}

TEST(Basket, BasketTotalDelete) {
  Basket b;
  Product p1("P1", "Product 1", 100.5);
  Product p2("P2", "Product 2", 200.5);
  Product p3("P3", "Product 3", 300.5);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  EXPECT_FLOAT_EQ(601.5,b.GetTotal());
  b.DeleteProduct(p3);
  EXPECT_FLOAT_EQ(301.0,b.GetTotal());
  b.DeleteProduct(p2);
  EXPECT_FLOAT_EQ(100.5,b.GetTotal());
  b.DeleteProduct(p1);
  EXPECT_FLOAT_EQ(0.0,b.GetTotal());
}

TEST(Basket, BasketTotalDeleteQuantities) {
  Basket b;
  Product p1("P1", "Product 1", 100.5);
  Product p2("P2", "Product 2", 200.5);
  Product p3("P3", "Product 3", 300.5);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  EXPECT_FLOAT_EQ(601.5,b.GetTotal());

  b.AddProduct(p1);
  EXPECT_FLOAT_EQ(702.0,b.GetTotal());
  b.AddProduct(p1);
  EXPECT_FLOAT_EQ(802.5,b.GetTotal());


  b.DeleteProduct(p1);
  EXPECT_FLOAT_EQ(702.0,b.GetTotal());
  b.DeleteProduct(p1);
  EXPECT_FLOAT_EQ(601.5,b.GetTotal());
  b.DeleteProduct(p1);
  EXPECT_FLOAT_EQ(501.0,b.GetTotal());
}

TEST(Basket, Basket_get_ids_empty) {
  Basket b;
  std::vector<std::string> vs;
  vs=b.GetIds();
  EXPECT_EQ(0, vs.size());
}
TEST(Basket, Basket_get_ids) {
  Basket b;
  Product p1("P1", "Product 1", 100.5);
  Product p2("P2", "Product 2", 200.5);
  Product p3("P3", "Product 3", 300.5);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  std::vector<std::string> vs;
  vs=b.GetIds();
  EXPECT_EQ(3, vs.size());
  EXPECT_EQ(vs[0], "P1");
  EXPECT_EQ(vs[1], "P2");
  EXPECT_EQ(vs[2], "P3");
  b.DeleteProduct(p3);
  vs=b.GetIds();
  EXPECT_EQ(2, vs.size());
  EXPECT_EQ(vs[0], "P1");
  EXPECT_EQ(vs[1], "P2");
  b.AddProduct(p1);
  vs=b.GetIds();
  EXPECT_EQ(2, vs.size());
  EXPECT_EQ(vs[0], "P1");
  EXPECT_EQ(vs[1], "P2");
  b.DeleteProduct(p1);
  vs=b.GetIds();
  EXPECT_EQ(2, vs.size());
  EXPECT_EQ(vs[0], "P1");
  EXPECT_EQ(vs[1], "P2");
  b.DeleteProduct(p1);
  b.DeleteProduct(p2);
  vs=b.GetIds();
  EXPECT_EQ(0, vs.size());
}
TEST(Basket, Basket_get_qs_empty) {
  Basket b;
  std::vector<int> v;
  v=b.GetQs();
  EXPECT_EQ(0, v.size());
}
TEST(Basket, Basket_get_qs) {
  Basket b;
  Product p1("P1", "Product 1", 100.5);
  Product p2("P2", "Product 2", 200.5);
  Product p3("P3", "Product 3", 300.5);
  b.AddProduct(p1);
  b.AddProduct(p2);
  b.AddProduct(p3);
  std::vector<int> v;
  v=b.GetQs();
  EXPECT_EQ(3, v.size());
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(1, v[2]);
  b.AddProduct(p3);
  v=b.GetQs();
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(2, v[2]);
  b.AddProduct(p1);
  v=b.GetQs();
  EXPECT_EQ(2, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(2, v[2]);
  b.DeleteProduct(p1);
  b.DeleteProduct(p3);
  v=b.GetQs();
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(1, v[2]);
}
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}