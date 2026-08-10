#include "market.h"

int main(){
    std::string id, name, town, province, country, maker, seller, sector, slogan;
    double rank, price, inch;
    int age, entry_year, op, premium;
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
    std::cout << "inch: ";
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
    //Client
    std::cout << "\n\nTipo de cliente: ";
    std::cin >> premium;
    Client c1(id, name, town, province, country, age, rank, entry_year, premium);
    c1.SetPremium(premium);
    std::cout << "Cliente 1 tipo: " << c1.GetPremium() << "\n";
    //Seller
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
    Seller s1(id, name, town, province, country, age, rank, entry_year, sector);
    s1.SetSector(sector);
    std::cout << "Producto 1 Tipo de producto: " << s1.GetSector();
    //Market
    std::cout << "\nSlogan de tu tienda: ";
    std::cin >> slogan;
    Market m1(slogan);
    m1.SetSlogan(slogan);
    std::cout << "Slogan de tu tienda: " << m1.GetSlogan() << "\n";

    //Person
    std::cout << "Persona 2:\n"
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
    std::cout << "inch: ";
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
    //Basket
    //Client
    std::cout << "\n\nTipo de cliente: ";
    std::cin >> premium;
    Client c2(id, name, town, province, country, age, rank, entry_year, premium);
    c2.SetPremium(premium);
    std::cout << "Cliente 2 tipo: " << c2.GetPremium() << "\n";
    //Seller
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
                sector="empty";
                break;
        }
        std::cout << "\n";
    }
    Seller s2(id, name, town, province, country, age, rank, entry_year, sector);
    s2.SetSector(sector);
    std::cout << "Producto 2 Tipo de producto: " << s2.GetSector() << "\n";
    //Market
    std::cout << "\nSlogan de tu tienda: ";
    std::cin >> slogan;
    Market m2(slogan);
    m2.SetSlogan(slogan);
    std::cout << "Slogan de tu tienda: " << m2.GetSlogan() << "\n";
    /*
    SetSlogan();
    AddClient();
    AddSeller();
    NClients();
    NSellers();
    DeleteClient();
    DeleteSeller();
    AddProductSeller();
    AddProductClient();
    DeleteProductSeller();
    DeleteProductClient();
    GetMoneyInBasket();
    DumpMarket();
    muestraC();
    muestraV();
    muestraP();
    muestraClient();
    muestraSeller();
    */
    return 0;
}