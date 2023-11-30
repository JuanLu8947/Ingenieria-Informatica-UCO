#include "product.h"

Product::Product(std::string id, std::string name, double price, std::string maker, std::string seller){
    id_=id;
    name_=name;
    price_=price;
    maker_=maker;
    seller_=seller;
            
    name= "empty";
    price = 0.0;
    maker = "empty";
    seller = "empty";
}