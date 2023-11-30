#include "product.h"

int main(){

    std::string id, name, maker, seller;
    double price;

    std::cout << "id: " << "\n";
    std::cin >> id;
    std::cout << "name: " << "\n";
    std::cin >> name;
    std::cout << "price: " << "\n";
    std::cin >> price;
    std::cout << "maker: " << "\n";
    std::cin >> maker;
    std::cout << "seller" << "\n";
    std::cin >> seller;
    
    Product p1(id, name, price, maker, seller);


    std::cout << "id: " << "\n";
    std::cin >> id;
    std::cout << "name: " << "\n";
    std::cin >> name;
    std::cout << "price: " << "\n";
    std::cin >> price;
    std::cout << "maker: " << "\n";
    std::cin >> maker;
    std::cout << "seller" << "\n";
    std::cin >> seller;

    Product p2(id, name, price, maker, seller);

    
    p1.GetDataStr();
    p2.GetDataStr();
}