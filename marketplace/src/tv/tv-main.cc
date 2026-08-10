#include "product.h"
#include "tv.h"

int main(){
    std::string id, name, maker, seller;
    double price, inch;
    //Product-TV   
    std::cout << "TV 1:\n"
              << "id: ";
    std::cin >> id;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "price: ";
    std::cin >> price;
    std::cout << "maker: ";
    std::cin >> maker;
    std::cout << "seller: ";
    std::cin >> seller;
    std::cout << "inch: ";
    std::cin >> inch;
    Tv t1(id, name, price, maker, seller, inch);
    Product p1(id, name, price, maker, seller);
    std::cout << "\n" << t1.GetDataStr(p1);

    //Product-TV    
    std::cout << "\n\nTV 2:\n"
              << "id: ";
    std::cin >> id;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "price: ";
    std::cin >> price;
    std::cout << "maker: ";
    std::cin >> maker;
    std::cout << "seller: ";
    std::cin >> seller;
    Tv t2(id, name, price, maker, seller, inch);
    Product p2(id, name, price, maker, seller);
    std::cout << "\n" << t2.GetDataStr(p2);
}