#include <iostream>
#include <string>
#include "market.h"

int main(){
    int op;
    double price;
    std::string client_id, seller_id, product_id, slogan, client_name, seller_name, name, maker;
    std::cout<<"Slogan para tu tienda: ";
    getline(std::cin, slogan);
    Market m(slogan);

    Client c1("C1", "Juan");
    Client c2("C2", "Oc");
    Client c3("C3", "Pepe");
    Client c4("C4", "Quicky");
    Client c5("C5", "Nyan");

    Seller s1("S1", "A.");
    Seller s2("S2", "Maru");
    Seller s3("S3", "Pili");
    Seller s4("S4", "Abel");
    Seller s5("S5", "Bill Gates");

    if(!m.AddClient(c1)){
        std::cout<<"ERROR AL AÑADIR CLIENTE 1"<<std::endl;
    }
    if(!m.AddClient(c2)){
        std::cout<<"ERROR AL AÑADIR CLIENTE 2"<<std::endl;
    }
    if(!m.AddClient(c3)){
        std::cout<<"ERROR AL AÑADIR CLIENTE 3"<<std::endl;
    }
    if(!m.AddClient(c4)){
        std::cout<<"ERROR AL AÑADIR CLIENTE 4"<<std::endl;
    }
    if(!m.AddClient(c5)){
        std::cout<<"ERROR AL AÑADIR CLIENTE 5"<<std::endl;
    }

    if(!m.AddSeller(s1)){
        std::cout<<"ERROR AL AÑADIR VENDEDOR 1"<<std::endl;
    }
    if(!m.AddSeller(s2)){
        std::cout<<"ERROR AL AÑADIR VENDEDOR 2"<<std::endl;
    }
    if(!m.AddSeller(s3)){
        std::cout<<"ERROR AL AÑADIR VENDEDOR 3"<<std::endl;
    }
    if(!m.AddSeller(s4)){
        std::cout<<"ERROR AL AÑADIR VENDEDOR 4"<<std::endl;
    }
    if(!m.AddSeller(s5)){
        std::cout<<"ERROR AL AÑADIR VENDEDOR 5"<<std::endl;
    }

    Product p1("TVX001", "SAMSUNG HD VERSION 1.2", 250.00, "SAMSUNG", "Lian");
    Product p2("TVX002", "LG HD VERSION 1.4", 300.00, "LG ELECTRONICS", "Sergy Astof");
    Product p3("GrX001", "Mesa de billar profesional", 140.00, "Billar Stars", "Marien Antonelly");
    Product p4("PCX001", "ASUS TUF GAMING 505DT",900.00, "ASUS", "Kaji Komo");
    Product p5("PCX002", "MSI RAIDER", 1200.00, "MSI", "Andresi Mendelez");
    m.AddProductSeller(p1, s1.GetId());
    m.AddProductSeller(p2, s2.GetId());
    m.AddProductSeller(p3, s3.GetId());
    m.AddProductSeller(p4, s4.GetId());
    m.AddProductSeller(p5, s5.GetId());
    
    do{
        std::cout<<"\n1. Añadir Cliente\n" <<"2. Añadir Vendedor\n"
        <<"3. Añadir Producto a la cesta (id del producto, id del cliente)\n"
        <<"4. Borrar Producto de la cesta (id del producto, id del cliente)\n"
        <<"5. Mostrar el Ticket de la compra en un fichero\n"
        <<"6. Mostrar el Ticket de la compra en pantalla\n"
        <<"7. Mostrar el Slogan de la Tienda\n" 
        <<"8. Salir de la Tienda\n";
        std::cout<<"--->";
        std::cin>>op;
        switch(op){
            case 1:{
                std::cout << "Introduzca id de cliente: ";
                std::cin >> client_id;
                std::cout << "Introduzca nombre de cliente: ";
                std::cin >> client_name;
                Client c(client_id, client_name);
                if(!m.AddClient(c)){
                    std::cout<<"ERROR AL AÑADIR CLIENTE "<<std::endl;
                }
                break;
            }
            case 2:{
                std::cout << "Introduzca id de vendedor: ";
                std::cin >> seller_id;
                std::cout << "Introduzca nombre de vendedor: ";
                std::cin >> seller_name;
                Seller s(seller_id, seller_name);
                if(!m.AddSeller(s)){
                    std::cout<<"ERROR AL AÑADIR VENDEDOR "<<std::endl;
                }
                break;
            }
            case 3:{
                std::cout << "Estos son los clientes existentes:\n";
                m.muestraC();
                std::cout << "Selecciona id de cliente:\n ";
                std::cout<<"-->";
                getline(std::cin, client_id);
                getline(std::cin, client_id);
                if(!m.muestraClient(client_id)){
                    std::cout << "ERROR. Este cliente no existe\n";
                    break;
                }
                std::cout << "\nEstos son los productos disponibles:\n";
                m.muestraP();
                std::cout << "Selecciona id de producto: ";
                std::cout<<"-->";
                getline(std::cin, product_id);
                std::cout<<product_id<<std::endl;
                
                if(product_id == p1.GetId()){
                    m.AddProductClient(p1, client_id);
                }
                else if(product_id == p2.GetId()){
                    m.AddProductClient(p2, client_id);
                }
                else if(product_id == p3.GetId()){
                    m.AddProductClient(p3, client_id);
                }
                else if(product_id == p4.GetId()){
                    m.AddProductClient(p4, client_id);
                }
                else if(product_id == p5.GetId()){
                    m.AddProductClient(p5, client_id);
                } 
                break;
            }
            case 4:{
                std::cout << "Estos son los clientes existentes:\n";
                m.muestraC();
                std::cout << "Selecciona id de cliente:\n ";
                std::cout<<"-->";
                getline(std::cin, client_id);
                getline(std::cin, client_id);
                if(!m.muestraClient(client_id)){
                    std::cout << "ERROR. Este cliente no existe\n";
                    break;
                }
                std::cout << "\nEstos son los productos disponibles:\n";
                m.muestraP();
                std::cout << "Selecciona id de producto: ";
                std::cout<<"-->";
                getline(std::cin, product_id);                

                if(product_id == p1.GetId()){
                    m.DeleteProductClient(p1, client_id);
                }
                else if(product_id == p2.GetId()){
                    m.DeleteProductClient(p2, client_id);
                }
                else if(product_id == p3.GetId()){
                    m.DeleteProductClient(p3, client_id);
                }
                else if(product_id == p4.GetId()){
                    m.DeleteProductClient(p4, client_id);
                }
                else if(product_id == p5.GetId()){
                    m.DeleteProductClient(p5, client_id);
                }
                break;
            }
            case 5:
                m.DumpMarket(0);
                break;
            case 6:
                m.DumpMarket(1);
                break;
            case 7:
                std::cout << "Slogan: "  << slogan << "\n";
                break;
            default:
                std::cout<<"Hasta la proxima"<<std::endl;
                break;
        }
    }while(op!=8);
}