#include "computer.h"

int main(){

    std::string id, name, maker, seller;
    double price, inch;
    int op;
    ComputerType type;
    /* En Product
    std::cout << "id: ";
    std::cin >> id;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "price: ";
    std::cin >> price;
    std::cout << "maker: ";
    std::cin >> maker;
    std::cout << "seller: ";
    std::cin >> seller;
    //En TV
    std::cout << "inch: ";
    std::cin >> inch;
    */
    std::cout << "Type:\n"
    << "1. Desktop\n"
    << "2. Laptop\n"
    << "3. Server\n"
    << "4. Tablet\n"
    << "5. Gaming\n";
    std::cin >> op;
    switch(op){
        case 1: //D
            type = ComputerType::Desktop;
            break;
        case 2: //L
            type = ComputerType::Laptop;
            break;
        case 3: //S
            type = ComputerType::Server;
            break;
        case 4: //T
            type = ComputerType::Tablet;
            break;
        case 5: //G
            type = ComputerType::Gaming;
            break;
        default:
            break;
    }

    Computer p1(id, type, name, price, maker, seller);

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
    std::cin >> seller;
    //En TV
    std::cout << "inch: " << "\n";
    std::cin >> inch;
    */
    std::cout << "Type:\n"
    << "1. Desktop\n"
    << "2. Laptop\n"
    << "3. Server\n"
    << "4. Tablet\n"
    << "5. Gaming\n";
    std::cin >> op;
    switch(op){
        case 1: //D
            type = ComputerType::Desktop;
            break;
        case 2: //L
            type = ComputerType::Laptop;
            break;
        case 3: //S
            type = ComputerType::Server;
            break;
        case 4: //T
            type = ComputerType::Tablet;
            break;
        case 5: //G
            type = ComputerType::Gaming;
            break;
        default:
            break;
    }
    
    Computer p2(id, type, name, price, maker, seller);

    
    p1.GetDataStr();
    p2.GetDataStr();
}