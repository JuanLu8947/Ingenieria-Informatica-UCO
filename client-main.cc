#include "client.h"

int main(){
    
    std::string id, name, town, province, country; 
    int age, entry_year, premium;
    double rank;
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
    //En Computer
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
    }*/
    std::cout << "Tipo de cliente: ";
    std::cin >> premium;
    

    Client p1(id, name, town, province, country, age, rank, entry_year, premium);
    p1.SetPremium(premium);
    std::cout << "Cliente 1 tipo: " <<p1.GetPremium();

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
    //En Computer
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
    }*/
    std::cout << "\n\nTipo de cliente: ";
    std::cin >> premium;
    
    Client p2(id, name, town, province, country, age, rank, entry_year, premium);
    p2.SetPremium(premium);
    std::cout << "Cliente 2 tipo: " << p2.GetPremium() << "\n";
    return 0;
}