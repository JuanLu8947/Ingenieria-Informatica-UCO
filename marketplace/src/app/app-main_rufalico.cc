#include "market.h"
#include <list>
#include <iostream>

int main()
{
    Market mercado("Al carro lo barato!");
    Client cliente1("XX1");
    Client cliente2("XX2");
    Client cliente3("XX3");
    Client cliente4("XX4");
    Client cliente5("XX5");

    Seller vendedor1("XX6");
    Seller vendedor2("XX7");
    Seller vendedor3("XX8");
    Seller vendedor4("XX9");
    Seller vendedor5("XX10");

    Product p1("PP1", "tv", 2345.9);
    Product p2("PP2", "mouse", 10.35);
    Product p3("PP3", "movil", 299.99);
    Product p4("PP4", "pc gaming", 2000.00);
    Product p5("PP5", "pato", 9999.99);

    std::list<Product> vecProd;
    vecProd.push_back(p1);
    vecProd.push_back(p2);
    vecProd.push_back(p3);
    vecProd.push_back(p4);
    vecProd.push_back(p5);


    mercado.AddClient(cliente1);
    mercado.AddClient(cliente2);
    mercado.AddClient(cliente3);
    mercado.AddClient(cliente4);
    mercado.AddClient(cliente5);

    mercado.AddSeller(vendedor1);
    mercado.AddSeller(vendedor2);
    mercado.AddSeller(vendedor3);
    mercado.AddSeller(vendedor4);
    mercado.AddSeller(vendedor5);

    mercado.AddProductSeller(p1, "XX6");
    mercado.AddProductSeller(p2, "XX6");
    mercado.AddProductSeller(p3, "XX6");
    mercado.AddProductSeller(p4, "XX6");
    mercado.AddProductSeller(p5, "XX6");

    mercado.AddProductSeller(p1, "XX7");
    mercado.AddProductSeller(p2, "XX7");
    mercado.AddProductSeller(p3, "XX7");
    mercado.AddProductSeller(p4, "XX7");
    mercado.AddProductSeller(p5, "XX7");

    mercado.AddProductSeller(p1, "XX8");
    mercado.AddProductSeller(p2, "XX8");
    mercado.AddProductSeller(p3, "XX8");
    mercado.AddProductSeller(p4, "XX8");
    mercado.AddProductSeller(p5, "XX8");

    mercado.AddProductSeller(p1, "XX9");
    mercado.AddProductSeller(p2, "XX9");
    mercado.AddProductSeller(p3, "XX9");
    mercado.AddProductSeller(p4, "XX9");
    mercado.AddProductSeller(p5, "XX9");

    mercado.AddProductSeller(p1, "XX10");
    mercado.AddProductSeller(p2, "XX10");
    mercado.AddProductSeller(p3, "XX10");
    mercado.AddProductSeller(p4, "XX10");
    mercado.AddProductSeller(p5, "XX10");


    std::string tempId, tempIdProd;
    Client ClTemp ("a");
    Seller SlTemp ("b");
    int opcion = 0;


    while (opcion != 7)
    {
        std::cout << "1. Añadir cliente." <<'\n';
        std::cout << "2. Añadir vendedor" <<'\n';
        std::cout << "3. Añadir producto en la cesta de un cliente" <<'\n';
        std::cout << "4. Borrar producto de la cesta de un cliente" <<'\n';
        std::cout << "5. Volcar datos el fichero de salida ventas.txt" <<'\n';
        std::cout << "6. Volcar datos a pantalla" <<'\n';
        std::cout << "7. Salir del programa" <<'\n';
        std::cin >> opcion;
        switch (opcion)
        {
            case 1:
                std::cout << "Escriba la id del cliente\n";
                std::cin >> tempId;
                ClTemp.SetId(tempId);
                
                if (mercado.AddClient(ClTemp))
                {
                    std::cout << "Cliente añadido con exito\n";
                }
                else std::cout << "No se ha podido añadir el cliente\n";
                break;

            case 2:
                std::cout << "Escriba la id del vendedor\n";
                std::cin >> tempId;
                SlTemp.SetId(tempId);
                if (mercado.AddSeller(SlTemp))
                {
                    std::cout << "Seller añadido con exito\n";
                }
                else std::cout << "No se ha podido añadir el vendedor\n";
                break;
            
            case 3: 

                std::cout << "Escriba el id del cliente\n";
                std::cin >> tempId;
                std::cout << "Escriba el id del producto\n";
                std::cin >> tempIdProd;
                for (auto it = vecProd.begin(); it != vecProd.end(); ++it)
                {
                    if (it->GetId() == tempIdProd)
                    {
                        if (mercado.AddProductClient(*it, tempId))
                        {
                            std::cout << "Producto añadido al cliente con exito\n";
                        }
                        else
                        {
                            std::cout << "ERROR: No se ha podido añadir el producto al cliente\n";
                        }
                    }
                }
                break;

            case 4:
                std::cout << "Escriba la id del cliente\n";
                std::cin >> tempId;
                std::cout << "Escriba la id del producto\n";
                std::cin >> tempIdProd;
                for (auto it = vecProd.begin(); it != vecProd.end(); ++it)
                {
                    if (it->GetId() == tempIdProd)
                    {
                        if (mercado.DeleteProductClient(*it, tempId))
                        {
                            std::cout << "Producto borrado al cliente con exito\n";
                        }
                        else
                        {
                            std::cout << "ERROR: No se ha podido borrar el producto\n";
                        }
                    }
                }
                break;

            case 5:
                mercado.DumpMarket(1);
                break;

            case 6:
                mercado.DumpMarket(0);
                break;

            case 7:
                std::cout << "Saliendo...\n";
                break;

            case 8:
                std::cout << mercado.NClients() << '\n';

            default:
                std::cout << "ERROR: Escoja una opcion valida\n";
        }
    }
}