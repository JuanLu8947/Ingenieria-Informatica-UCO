#include "market.h"


int main(){

    std::string slogan;
    std::cout<<"Crea El Eslogan para tu Tienda\n";
    getline(std::cin, slogan);
    Market tienda(slogan);
    Client quicky("Quickiller", "Quiky", "Córdoba", "Córdoba", "EspaÑa", 2, 1, 2023, 1), fran("Fran", "Fran", "Córdoba", "Córdoba", "EspaÑa", 3, 2, 2023, 6), Jose("Oc", "Jóse", "Córdoba", "Córdoba", "EspaÑa", 1, 2, 2023, 3), alvaro("Álvaro", "Álvaro", "Córdoba", "Córdoba", "EspaÑa", 19, 80, 2023, 100), sus("ඞ", "ඞ", "Impostor", "Es", "el sus", 999, 999, 2023, 999);
    Seller oo("oo", "oo"), oc("oc", "oc"), co("co", "co"), cc("cc", "cc"), coo("coo", "coo");
    tienda.AddClient(quicky);
    tienda.AddClient(Jose);
    tienda.AddClient(fran);
    tienda.AddClient(alvaro);
    tienda.AddClient(sus);
    tienda.AddSeller(oo);
    tienda.AddSeller(oc);
    tienda.AddSeller(co);
    tienda.AddSeller(cc);
    tienda.AddSeller(coo);
    int menu=1;

    while(menu!=9 || menu<1 || menu>9){

        std::cout
        <<"1 --> Añadir Cliente\n"
        <<"2 --> Añadir Vendedor\n"
        <<"3 --> Añade un producto a tu stock\n"
        <<"4 --> Añadir Producto a la cesta (id del producto, id del cliente)\n"
        <<"5 --> Borrar Producto de la cesta (id del producto, id del cliente)\n"
        <<"6 --> Mostrar el Ticket de la compra en un fichero\n"
        <<"7 --> Mostrar el Ticket de la compra en pantalla\n"
        <<"8 --> Mostrar el Slogan de la Tienda\n"
        <<"9 --> Salir de la Tienda\n";
        std::cin>>menu;

        switch(menu){

        case 1:
        {
            std::string id_cliente, nombre_cliente;
            std::cout<<"Ingrese su id de Cliente\n";
            std::cin>>id_cliente;
            std::cout<<"Ingrese su nombre\n";
            std::cin>>nombre_cliente;
            Client c(id_cliente, nombre_cliente);
            tienda.AddClient(c);

            break;
        }

        case 2:
        {
            std::string id_vendedor, nombre_vendedor;
            std::cout<<"Ingrese su id de Vendedor\n";
            std::cin>>id_vendedor;
            std::cout<<"Ingrese su nombre\n";
            std::cin>>nombre_vendedor;
            Seller s(id_vendedor, nombre_vendedor);
            tienda.AddSeller(s);

            break;            
        }


        case 3:
        {
            std::string id_vendedor;
            std::cout<<"Estos son los Vendedores disponibles\n";
            //tienda.MostrarVendedores();
            tienda.muestraV();
            std::cin>>id_vendedor;

            std::string p_id, p_name, p_maker, p_seller;
            float p_price;
            std::cout<<"¿ID del Producto?\n";
            std::cin>>p_id;
            std::cout<<"¿Nombre del Producto?\n";
            std::cin>>p_name;
            std::cout<<"¿Presio?\n";
            std::cin>>p_price;
            std::cout<<"¿Fabricante del Producto?\n";
            std::cin>>p_maker;
            std::cout<<"¿Nombre del Vendedor?\n";
            std::cin>>p_seller;
            Product p(p_id, p_name, p_price, p_maker, p_seller);
            tienda.AddProductSeller(p, id_vendedor);
            break;
            
        }



        case 4:
        {

            /*if(*/tienda.muestraP();//){
                std::string id_cliente, id_producto;
                std::cout<<"Estos son los Clientes disponibles\n";
                //tienda.MostrarClientes();
                tienda.muestraC();
                std::cin>>id_cliente;
                std::cout<<"Estos son los productos disponibles\n\n";
                //tienda.MostrarProductos(1);
                tienda.muestraP();
                std::cin>>id_producto;
                Product p(id_producto);
                tienda.AddProductClient(p, id_cliente);
            //{}
            /*else{
                std::cout<<"No Hay Productos Disponbles Actualmente\n ->Espera a que Haya nuevo Stock\n\n";
            }*/
            break;
            
        }

        case 5:
        {
            std::string id_cliente, id_producto;
            std::cout<<"Estos son los Clientes disponibles\n";
            tienda.muestraC();
            std::cout<<"\n";
            std::cin>>id_cliente;            
            //if(tienda.muestraClient(id_cliente)){
            /*if(*/tienda.muestraClient(id_cliente);//){
                std::cout<<"↑ Estos son los productos de tu cesta\n";
                std::cin>>id_producto;
                Product p(id_producto);
                tienda.DeleteProductClient(id_producto, id_cliente);
                std::cout<<"\n";
            //}
            /*else{
                std::cout<<"Ese cliente no existe o no tiene ningun producto en su cesta\n\n";
            }*/
            break;
            
        }

        case 6:
            tienda.DumpMarket(1);
            std::cout<<"El recibo estará en la carpeta de este programa\n";
            break;
        

        case 7:
            tienda.DumpMarket(0);
            break;

        case 8:
            std::cout<<"\n";
            std::cout<<" -> "<<slogan<<std::endl;
            std::cout<<"\n";
            break;
    }



    
}
}