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
    Product p3("GrX001", "Mesa de billar semiprofesional", 730.00, "Billar Stars", "Marien Antonelly");
    Product p4("PCX001", "ASUS TUF GAMING 505DT", 900.00, "ASUS", "Kaji Komo");
    Product p5("PCX002", "MSI RAIDER", 1900.00, "MSI", "Andresi Mendelez");
    m.AddProductSeller(p1, s1.GetId());
    m.AddProductSeller(p2, s1.GetId());
    m.AddProductSeller(p3, s1.GetId());
    m.AddProductSeller(p4, s1.GetId());
    m.AddProductSeller(p5, s1.GetId());

    Product p6("TVX003", "Sony Bravia 43X80L", 679.00, "SONY", "Lester");
    Product p7("TVX004", "Philips 32PFS6908", 260.00, "PHILIPS", "Astovi");
    Product p8("GrX002", "Air Hockey Table", 100.00, "Hockey Stars", "Anton");
    Product p9("PCX002", "ASUS ROG G513RC", 1100.00, "ASUS", "Kaji Komo");
    Product p10("PCX003", "MSI Bravo 15 C7VE-288XES", 800.00, "MSI", "Andresi Mendelez");
    m.AddProductSeller(p6, s2.GetId());
    m.AddProductSeller(p7, s2.GetId());
    m.AddProductSeller(p8, s2.GetId());
    m.AddProductSeller(p9, s2.GetId());
    m.AddProductSeller(p10, s2.GetId());

    Product p11("TVX005", "Xiaomi TV A2 HDR10", 260.00, "XIAOMI", "Xiaon-Lu");
    Product p12("TVX006", "Toshiba 32LV3E63DG", 200.00, "TOSHIBA", "Serg Mastov");
    Product p13("GrX003", "Mesa de billar profesional", 1142.00, "Billar Stars", "Marien Antonelly");
    Product p14("PCX005", "ASUS TUF Gaming F15 FX506LHB-HN324", 960.00, "ASUS", "Kaji Komo");
    Product p15("PCX006", "MSI GP65 Leopard 10SDK-817XES", 960.00, "MSI", "Andresi Mendelez");
    m.AddProductSeller(p11, s3.GetId());
    m.AddProductSeller(p12, s3.GetId());
    m.AddProductSeller(p13, s3.GetId());
    m.AddProductSeller(p14, s3.GetId());
    m.AddProductSeller(p15, s3.GetId());
    
    Product p16("TVX007", "Panasonic TX-43LX650E", 295.00, "PANASONIC", "Leo");
    Product p17("TVX008", "JVC 43VA3200", 208.00, "JVC", "Gerai");
    Product p18("GrX004", "Peradix Ajedrez Madera", 30.00, "PERADIX", "Perei Parai");
    Product p19("PCX007", "ASUS TUF GAMING A15 2023 FA507NV-LP031W", 1199.00, "ASUS", "Kaji Komo");
    Product p20("PCX008", "MSI Katana 15 B12VFK-1412XES", 969.00, "MSI", "Andresi Mendelez");
    m.AddProductSeller(p16, s4.GetId());
    m.AddProductSeller(p17, s4.GetId());
    m.AddProductSeller(p18, s4.GetId());
    m.AddProductSeller(p19, s4.GetId());
    m.AddProductSeller(p20, s4.GetId());

    Product p21("TVX009", "Hisense 43A6K", 250.00, "HISENSE", "Niel");
    Product p22("TVX0010", "Hyundai HY32F5021AW", 203.00, "HYUNDAI", "Hui-Casei");
    Product p23("GrX005", "Mesa de bola de bolos", 29.00, "Bowling Stars", "Nelma");
    Product p24("PCX009", "ASUS VivoBook 16X K3605ZV-N1084", 1199.00, "ASUS", "Kaji Komo");
    Product p25("PCX0010", "MSI Pulse 15 B13VFK-444XES", 1399.00, "MSI", "Andresi Mendelez");
    m.AddProductSeller(p21, s5.GetId());
    m.AddProductSeller(p22, s5.GetId());
    m.AddProductSeller(p23, s5.GetId());
    m.AddProductSeller(p24, s5.GetId());
    m.AddProductSeller(p25, s5.GetId());
    
    std::list<Product> vP;
    vP.push_back(p1); vP.push_back(p2); vP.push_back(p3); vP.push_back(p4); vP.push_back(p5);
    vP.push_back(p6); vP.push_back(p7); vP.push_back(p8); vP.push_back(p9); vP.push_back(p10);
    vP.push_back(p11); vP.push_back(p12); vP.push_back(p13); vP.push_back(p14); vP.push_back(p15); 
    vP.push_back(p16); vP.push_back(p17); vP.push_back(p18); vP.push_back(p19); vP.push_back(p20);
    vP.push_back(p21); vP.push_back(p22); vP.push_back(p23); vP.push_back(p24); vP.push_back(p25); 

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
                std::cout << "Selecciona id de cliente: ";
                std::cin >> client_id;
                if(!m.muestraClient(client_id)){
                    std::cout << "ERROR. Este cliente no existe\n";
                    break;
                }
                std::cout << "\nEstos son los productos disponibles:\n";
                m.muestraP();
                std::cout << "Selecciona id de producto: ";
                std::cin >> product_id;

                std::list<Product>::iterator it;
                for (it = vP.begin(); it!=vP.end(); ++it){
                    if ((*it).GetId() == product_id){
                        if (m.AddProductClient(*it, client_id)){
                            std::cout << "Producto añadido correctamente\n";
                        }
                        else{
                            std::cout << "ERROR. El producto no pudo ser añadido correctamente\n";
                        }
                    }
                }
                /*
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
                else if(product_id == p6.GetId()){
                    m.AddProductClient(p6, client_id);
                }
                else if(product_id == p7.GetId()){
                    m.AddProductClient(p7, client_id);
                }
                else if(product_id == p8.GetId()){
                    m.AddProductClient(p8, client_id);
                }
                else if(product_id == p9.GetId()){
                    m.AddProductClient(p9, client_id);
                }
                else if(product_id == p10.GetId()){
                    m.AddProductClient(p10, client_id);
                }
                else if(product_id == p11.GetId()){
                    m.AddProductClient(p11, client_id);
                }
                else if(product_id == p12.GetId()){
                    m.AddProductClient(p12, client_id);
                }
                else if(product_id == p13.GetId()){
                    m.AddProductClient(p13, client_id);
                }
                else if(product_id == p14.GetId()){
                    m.AddProductClient(p14, client_id);
                }
                else if(product_id == p15.GetId()){
                    m.AddProductClient(p15, client_id);
                }
                else if(product_id == p16.GetId()){
                    m.AddProductClient(p16, client_id);
                }
                else if(product_id == p17.GetId()){
                    m.AddProductClient(p17, client_id);
                }
                else if(product_id == p18.GetId()){
                    m.AddProductClient(p18, client_id);
                }
                else if(product_id == p19.GetId()){
                    m.AddProductClient(p19, client_id);
                }
                else if(product_id == p20.GetId()){
                    m.AddProductClient(p20, client_id);
                }
                else if(product_id == p21.GetId()){
                    m.AddProductClient(p21, client_id);
                }
                else if(product_id == p22.GetId()){
                    m.AddProductClient(p22, client_id);
                }
                else if(product_id == p22.GetId()){
                    m.AddProductClient(p22, client_id);
                }
                else if(product_id == p23.GetId()){
                    m.AddProductClient(p23, client_id);
                }
                else if(product_id == p24.GetId()){
                    m.AddProductClient(p24, client_id);
                }
                else if(product_id == p25.GetId()){
                    m.AddProductClient(p25, client_id);
                }
                else{
                    std::cout << "ERROR. El producto no pudo ser añadido correctamente";
                }
                */
                break;
            }
            case 4:{
                std::cout << "Estos son los clientes existentes:\n";
                m.muestraClientBasket();
                std::cout << "Selecciona id de cliente: ";
                std::cin >> client_id;
                if(!m.muestraClient(client_id)){
                    std::cout << "ERROR. Este cliente no existe\n";
                    break;
                }
                std::cout << "\nEstos son los productos disponibles:";
                m.muestraProductBasket();
                std::cout << "\nSelecciona id de producto: ";
                std::cin >> product_id;

                std::list<Product>::iterator it;
                for (it = vP.begin(); it!=vP.end(); ++it){
                    if ((*it).GetId() == product_id){
                        if (m.DeleteProductClient(*it, client_id)){
                            std::cout << "Producto borrado correctamente\n";
                        }
                        else{
                            std::cout << "ERROR. El producto no pudo ser borrado correctamente\n";
                        }
                    }
                }
                /*
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
                else if(product_id == p6.GetId()){
                    m.DeleteProductClient(p6, client_id);
                }
                else if(product_id == p7.GetId()){
                    m.DeleteProductClient(p7, client_id);
                }
                else if(product_id == p8.GetId()){
                    m.DeleteProductClient(p8, client_id);
                }
                else if(product_id == p9.GetId()){
                    m.DeleteProductClient(p9, client_id);
                }
                else if(product_id == p10.GetId()){
                    m.DeleteProductClient(p10, client_id);
                }
                else if(product_id == p11.GetId()){
                    m.DeleteProductClient(p11, client_id);
                }
                else if(product_id == p12.GetId()){
                    m.DeleteProductClient(p12, client_id);
                }
                else if(product_id == p13.GetId()){
                    m.DeleteProductClient(p13, client_id);
                }
                else if(product_id == p14.GetId()){
                    m.DeleteProductClient(p14, client_id);
                }
                else if(product_id == p15.GetId()){
                    m.DeleteProductClient(p15, client_id);
                }
                else if(product_id == p16.GetId()){
                    m.DeleteProductClient(p16, client_id);
                }
                else if(product_id == p17.GetId()){
                    m.DeleteProductClient(p17, client_id);
                }
                else if(product_id == p18.GetId()){
                    m.DeleteProductClient(p18, client_id);
                }
                else if(product_id == p19.GetId()){
                    m.DeleteProductClient(p19, client_id);
                }
                else if(product_id == p20.GetId()){
                    m.DeleteProductClient(p20, client_id);
                }
                else if(product_id == p21.GetId()){
                    m.DeleteProductClient(p21, client_id);
                }
                else if(product_id == p22.GetId()){
                    m.DeleteProductClient(p22, client_id);
                }
                else if(product_id == p23.GetId()){
                    m.DeleteProductClient(p23, client_id);
                }
                else if(product_id == p24.GetId()){
                    m.DeleteProductClient(p24, client_id);
                }
                else if(product_id == p25.GetId()){
                    m.DeleteProductClient(p25, client_id);
                }
                else{
                    std::cout << "ERROR. El producto no pudo ser borrado correctamente";
                }*/
                break;
            }
            case 5:
                m.DumpMarket(1);
                break;
            case 6:
                m.DumpMarket(0);
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