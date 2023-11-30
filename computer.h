#ifndef COMPUTER_H
#define COMPUTER_H
#include "product.h"

enum class ComputerType{
    Desktop,
    Laptop,
    Server,
    Tablet,
    Gaming
};

class Computer : public Product{
    private:
        ComputerType type_;
    public: 
        Computer(std::string id, ComputerType type, std::string name="empty", double price=0.0, std::string maker="empty", std::string seller="empty"): Product(id, name, price, maker, seller){type_=type;}
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
        //En TV
        double GetInch(){return inch_;}
        bool SetInch(double inch){
            if(inch>0){
                inch_=inch;
                return true;
            }
            return false;
        }
        */
        ComputerType GetType(){return type_;}
        void SetType(ComputerType type){type_=type;}

        std::string GetDataStr(){
            std::string pc="PC:\n";
            /*pc += /*En Product 
            "id: " + id_ + "\n" + 
            "name: " + name_ + "\n" + 
            "price: " + std::to_string(price_) + "\n" + 
            "maker: " + maker_ + "\n" + 
            "seller: " + seller_ + "\n" + 
            "inch: " + std::to_string(inch_) + "\n"; */
            /*"type: " + type_ + "\n";*/
            return pc;
        }
};
#endif