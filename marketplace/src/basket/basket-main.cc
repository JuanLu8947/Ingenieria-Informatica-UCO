#include "basket.h"

int main(){
    std::string id, name, maker, seller;
    double price, inch;
    int op;
    //ComputerType type;

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
    //TV
    std::cout << "\nTV 1:\n"
              <<  "inch: ";
    std::cin >> inch;
    /*Computer
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
    //Basket
    std::cout << "\nCesta 1:\n";
    Basket b1;
    b1.AddProduct(p1);
    std::vector<std::string> v_Ids_1;
    v_Ids_1=b1.GetIds();
    std::vector<int> v_Qs_v1;
    v_Qs_v1=b1.GetQs();
    std::cout << "Tamaño de la cesta: " << b1.GetSize()
              << "\nPrecio total de la cesta: " << b1.GetTotal()
              << "\nIds: " << v_Ids_1[0]
              << "\nQs: " << v_Qs_v1[0]
              << "\nBorrando producto 1 usando Product p...";
    b1.DeleteProduct(p1);

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
    //TV
    std::cout << "\nTV 2:\n"
              << "inch: " << "\n";
    std::cin >> inch;
    /*Computer
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
    //Basket
    std::cout << "\nCesta 2:\n";
    Basket b2;
    b2.AddProduct(p2);
    std::vector<std::string> v_Ids_2;
    v_Ids_2=b2.GetIds();
    std::vector<int> v_Qs_v2;
    v_Qs_v2=b2.GetQs();
    std::cout << "Tamaño de la cesta: " << b2.GetSize()
              << "\nPrecio total de la cesta: " << b2.GetTotal()
              << "\nIds: " << v_Ids_2[0]
              << "\nQs: " << v_Qs_v2[0]
              << "\nBorrando producto 2 usando id...";
    b2.DeleteProduct(id);
    
    //Product
    std::cout << "\n\nProducto 3:\n"
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
    Product p3(id, name, price, maker, seller);
    //TV
    std::cout << "\nTV 2:\n"
              << "inch: " << "\n";
    std::cin >> inch;
    /*Computer
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
    //Basket
    std::cout << "\nCesta 3:\n";
    Basket b3;
    b3.AddProduct(p3);
    std::vector<std::string> v_Ids_3;
    v_Ids_3=b3.GetIds();
    std::vector<int> v_Qs_v3;
    v_Qs_v3=b3.GetQs();
    std::cout << "Tamaño de la cesta: " << b3.GetSize()
              << "\nPrecio total de la cesta: " << b3.GetTotal()
              << "\nIds: " << v_Ids_3[0]
              << "\nQs: " << v_Qs_v3[0]
              << "\nBorrando cesta...";
    b3.DeleteBasket();
    
    return 0;
}