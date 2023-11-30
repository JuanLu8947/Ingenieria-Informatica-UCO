#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>

class Product{
    private:
        std::string id_, name_, maker_, seller_;
        double price_;
    public: 
        Product(std::string id, std::string name= "empty", double price=0.0, std::string maker="empty", std::string seller="empty");
        std::string GetId(){return id_;}
        std::string GetName(){return name_;}
        double GetPrice(){return price_;}
        std::string GetMaker(){return maker_;}
        std::string GetSeller(){return seller_;}

        void SetId(std::string id){id_=id;}
        void SetName(std::string name){name_=name;}
        void SetPrice(double price){price_=price;}
        void SetMaker(std::string maker){maker_=maker;}
        void SetSeller(std::string seller){seller_=seller;}
    
        std::string GetDataStr(){
            std::string Pr="Product:\n";
            Pr += 
            "id: " + id_ + "\n" + 
            "name: " + name_ + "\n" + 
            "price: " + std::to_string(price_) + "\n" + 
            "maker: " + maker_ + "\n" + 
            "seller: " + seller_ + "\n";
            return Pr;
        }
};
#endif