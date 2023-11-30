#include "seller.h"

int main(){
    
    std::string id, name, town, province, country, sector; 
    int age, entry_year;
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
    }
    */
    int op=1;
    while(op!=0){
        std::cout << "1-Añadir producto\n"
             << "0-Salir del programa\n"
             << "Introduzca una opción: ";
        std::cin >> op;
        switch(op){
            case 1:
                std::cout << "Tipo de producto: ";
                std::cin >> sector;
            break;
            default: //salida
                break;
        }
        std::cout << "\n";
    }

    Seller p1(id, name, town, province, country, age, rank, entry_year, sector);
    p1.SetSector(sector);
    std::cout << "Producto 1 Tipo de producto: " << p1.GetSector();

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
    }
    */
    std::cout << "\n\nSeller 2:\n";
    op=1;
    while(op!=0){
        std::cout << "1-Añadir producto\n"
             << "0-Salir del programa\n"
             << "Introduzca una opción: ";
        std::cin >> op;
        switch(op){
            case 1:
                std::cout << "Tipo de producto: ";
                std::cin >> sector;
            break;
            default: //salida
                break;
        }
        std::cout << "\n";
    }
    sector="empty";
    Seller p2(id, name, town, province, country, age, rank, entry_year, sector);
    p2.SetSector(sector);
    std::cout << "Producto 2 Tipo de producto: " << p2.GetSector() << "\n";
    return 0;
}