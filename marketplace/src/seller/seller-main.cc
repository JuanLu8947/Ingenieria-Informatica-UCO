#include "seller.h"

int main(){
    std::string id, name, town, province, country, maker, seller, sector;
    double rank, price, inch;
    int age, entry_year, op;
    //ComputerType type;
    //Person
    std::cout << "Persona 1:\n"
              << "id: ";
    std::cin >> id;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "town: ";
    std::cin >> town;
    std::cout << "province: ";
    std::cin >> province;
    std::cout << "country: ";
    std::cin >> country;
    std::cout << "age: ";
    std::cin >> age;
    std::cout << "entry_year: ";
    std::cin >> entry_year;
    std::cout << "rank: ";
    std::cin >> rank;
    //Product
    std::cout << "\nProducto 1:\n"
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
    //TV
    std::cout << "\nTV 1:\n"
              << "inch: ";
    std::cin >> inch;
    /*//Computer
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
    }//*/
    std::cout << "\nSeller 1:\n";
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
                sector="empty";
                break;
        }
        std::cout << "\n";
    }

    Seller p1(id, name, town, province, country, age, rank, entry_year, sector);
    p1.SetSector(sector);
    std::cout << "Producto 1. Tipo de producto: " << p1.GetSector();

    //Person
    std::cout << "\n\nPersona 2:\n"
              << "id: ";
    std::cin >> id;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "town: ";
    std::cin >> town;
    std::cout << "province: ";
    std::cin >> province;
    std::cout << "country: ";
    std::cin >> country;
    std::cout << "age: ";
    std::cin >> age;
    std::cout << "entry_year: ";
    std::cin >> entry_year;
    std::cout << "rank: ";
    std::cin >> rank;
    //Product
    std::cout << "\nProducto 2:\n"
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
    //TV
    std::cout << "\nTV 2:\n"
              << "inch: ";
    std::cin >> inch;
    /*//Computer
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
    }//*/
    std::cout << "\nSeller 2:\n";
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
                sector="empty";
                break;
        }
        std::cout << "\n";
    }
    Seller p2(id, name, town, province, country, age, rank, entry_year, sector);
    p2.SetSector(sector);
    std::cout << "Producto 2. Tipo de producto: " << p2.GetSector() << "\n";
    return 0;
}