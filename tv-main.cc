#include "product.h"
#include "tv.h"

int main(){

    std::string id, name, maker, seller;
    double price, inch;
    /* En Product
    std::cout << "id: " << "\n";
    std::cin >> id;
    std::cout << "name: " << "\n";
    std::cin >> name;
    std::cout << "price: " << "\n";
    std::cin >> price;
    std::cout << "maker: " << "\n";
    std::cin >> maker;
    std::cout << "seller" << "\n";
    std::cin >> seller; */
    std::cout << "inch: " << "\n";
    std::cin >> inch;

    Tv p1(id, name, price, maker, seller, inch);

    /* En Product
    std::cout << "id: " << "\n";
    std::cin >> id;
    std::cout << "name: " << "\n";
    std::cin >> name;
    std::cout << "price: " << "\n";
    std::cin >> price;
    std::cout << "maker: " << "\n";
    std::cin >> maker;
    std::cout << "seller" << "\n";
    std::cin >> seller; */
    std::cout << "inch: " << "\n";
    std::cin >> inch;

    Tv p2(id, name, price, maker, seller, inch);

    
    p1.GetDataStr();
    p2.GetDataStr();
}