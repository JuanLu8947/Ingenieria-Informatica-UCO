#ifndef BASKET_H
#define BASKET_H
#include "product.h"
#include <vector>
#include <list>
#include <map>

class Basket{
    private:
        std::map<std::string,int> product_quantity_;
        std::list<Product> product_list_;
        double total_;
    public:
        Basket(){total_=0.0;}
        
        void AddProduct(Product p);
        bool DeleteProduct(Product p);
        bool DeleteProduct(std::string id);
        void DeleteBasket();
        int GetSize();
        float GetTotal();
        std::vector<std::string> GetIds();
        std::vector<int> GetQs();
    //
};

#endif