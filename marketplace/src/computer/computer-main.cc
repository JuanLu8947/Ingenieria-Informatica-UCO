#include "computer.h"

int main(){
    std::string id, name, maker, seller;
    double price;
    int op;
    ComputerType type;
    //Product
    std::cout << "Product 1:\n"
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
    //Computer
    std::cout << "\nComputerType 1:\n"
    << "1. Desktop\n"
    << "2. Laptop\n"
    << "3. Server\n"
    << "4. Tablet\n"
    << "5. Gaming\n";
    std::cout << "type: ";
    std::cin >> op;
        std::cout << "\nComputer 1:\n"
              << "id: " << p1.GetId() << "\n"
              << "name: " << p1.GetName() << "\n"
              << "price: " << p1.GetPrice() << "\n"
              << "maker: " << p1.GetMaker() << "\n"
              << "seller: " << p1.GetSeller() << "\n"
              << "type: ";
    switch(op){
        case 1: //D
            type = ComputerType::Desktop;
            std::cout << "Desktop";
            break;
        case 2: //L
            type = ComputerType::Laptop;
            std::cout << "Laptop";
            break;
        case 3: //S
            type = ComputerType::Server;
            std::cout << "Server";
            break;
        case 4: //T
            type = ComputerType::Tablet;
            std::cout << "Tablet";
            break;
        case 5: //G
            type = ComputerType::Gaming;
            std::cout << "Gaming";
            break;
        default:
            break;
    }
    Computer c1(id, type, name, price, maker, seller);

    //Product
    std::cout << "\n\n\nProduct 2:\n"
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
    //Computer
    std::cout << "\nComputerType 2:\n"
    << "1. Desktop\n"
    << "2. Laptop\n"
    << "3. Server\n"
    << "4. Tablet\n"
    << "5. Gaming\n";
    std::cout << "type: ";
    std::cin >> op;
        std::cout << "\nComputer 1:\n"
              << "id: " << p1.GetId() << "\n"
              << "name: " << p1.GetName() << "\n"
              << "price: " << p1.GetPrice() << "\n"
              << "maker: " << p1.GetMaker() << "\n"
              << "seller: " << p1.GetSeller() << "\n"
              << "type: ";
    switch(op){
        case 1: //D
            type = ComputerType::Desktop;
            std::cout << "Desktop";
            break;
        case 2: //L
            type = ComputerType::Laptop;
            std::cout << "Laptop";
            break;
        case 3: //S
            type = ComputerType::Server;
            std::cout << "Server";
            break;
        case 4: //T
            type = ComputerType::Tablet;
            std::cout << "Tablet";
            break;
        case 5: //G
            type = ComputerType::Gaming;
            std::cout << "Gaming";
            break;
        default:
            break;
    }
    Computer c2(id, type, name, price, maker, seller);
}