#include <iostream>
#include <string>
#include "market.h"

void muestraClient(){
    //
}

void muestraSeller(){
    //
}

int main(){
    int op;
    double price;
    std::string client_id, seller_id, product_id;
    Market m("BestQuality");
    std::cout << "Slogan: " << m.GetSlogan() << "\n";
    for (int i=0; i<5; i++){
        m.AddClient(Client("C" + std::to_string(i)));
        m.AddSeller(Seller("S" + std::to_string(i)));
        std::cout << "\nVendedor " << i+1 << ":\n";
        for(int j=0; j<5; j++){
            Product p("P" + std::to_string(j));
            m.AddProductSeller(p, std::to_string(i));
            price=rand()%900;
            p.SetPrice(price);
            std::cout << "Precio Producto " << j+1 << ": " << p.GetPrice() << "\n";
        }
    }
    do{
        std::cout << "\n1. Añadir cliente. \n2. Añadir vendedor.\n" <<
        "3. Añadir producto en la cesta de un cliente pidiendo su id de cliente y el id del producto." <<
        "\n4. Borrar producto de la cesta de un cliente pidiendo su id de cliente y el id del producto." <<
        "\n5. Volcar datos al fichero de salida ventas.txt.\n" <<
        "6. Volcar datos a pantalla. \n7. Salir del programa\n" <<
        "Elige una opcion: ";
        std::cin >> op;
        std::cout << "\n";
        switch(op){
            case 1:
                std::cout << "Introduzca cliente: ";
                std::cin >> client_id; 
                m.AddClient(Client(client_id));
                break;
            case 2:
                std::cout << "Introduzca vendedor: ";
                std::cin >> seller_id;
                m.AddSeller(Seller(seller_id));
                break;
            case 3:
                std::cout << "Introduzca id de cliente: ";
                std::cin >> client_id;
                std::cout << "Introduzca id de producto: ";
                std::cin >> product_id;
                m.AddProductClient(product_id, client_id);
                break;
            case 4:
                std::cout << "Introduzca id de cliente: ";
                std::cin >> client_id;
                std::cout << "Introduzca id de producto: ";
                std::cin >> product_id;
                m.DeleteProductClient(product_id, client_id);
                break;
            case 5:
                m.DumpMarket(0);
                break;
            case 6:
                m.DumpMarket(1);
                break;
            default:
                break;
            std::cout << "\n";
        }

    }while(op!=7);
    return 0;
}