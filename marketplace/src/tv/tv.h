#ifndef TV_H
#define TV_H
#include "product.h"

class Tv : public Product{
    private:
        double inch_;
    public: 
        Tv(std::string id, std::string name="empty", double price=0.0, std::string maker="empty", std::string seller="empty", double inch=0.0): Product(id, name, price, maker, seller){inch_=inch;}
        /*En Product:
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
        */

        double GetInch(){return inch_;}
        bool SetInch(double inch){
            if(inch>0){
                inch_=inch;
                return true;
            }
            return false;
        }

        //funciones extra 
        std::string GetDataStr(Product p){
            std::string tele="TV:\n", id=p.GetId(), name=p.GetName(), maker=p.GetMaker(), seller=p.GetSeller();
            double price=GetPrice();
            tele +=
            "id: " + id + "\n" + 
            "name: " + name + "\n" + 
            "price: " + std::to_string(price) + "\n" + 
            "maker: " + maker + "\n" + 
            "seller: " + seller + "\n"
            "inch: " + std::to_string(inch_) + "\n";
            return tele;
        }
};
#endif