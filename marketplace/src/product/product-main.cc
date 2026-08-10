#include "product.h"

int main(){

    std::string id, name, maker, seller;
    double price;
    //Product
    std::cout << "Producto 1:\n"
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
    Product p1(id, name, price, maker, seller);
    std::cout << "\n" << p1.GetDataStr();    

    //Product
    std::cout << "\n\nProducto 2:\n"
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
    Product p2(id, name, price, maker, seller);
    std::cout << "\n" << p2.GetDataStr();    

}