#include "market.h"


bool Market::AddClient(Client client){

    for(auto it=client_list_.begin() ; it!=client_list_.end() ; ++it){
        if(it->GetId()==client.GetId()){
            return false;
        }
    }

    client_list_.push_back(client.GetId());
    return true;
}


bool Market::AddSeller(Seller seller){

    for(auto it=seller_list_.begin() ; it!=seller_list_.end() ; ++it){
        if(it->GetId()==seller.GetId()){
            return false;
        }
    }

    seller_list_.push_back(seller.GetId());
    return true;
}

bool Market::DeleteClient(Client client){

    for(auto it=client_list_.begin() ; it!=client_list_.end() ; ++it){
        if(it->GetId()==client.GetId()){

            client_list_.erase(it);
            return true;
        }
        
    }
    return false;
}


bool Market::DeleteSeller(Seller seller){

    for(auto it=seller_list_.begin() ; it!=seller_list_.end() ; ++it){
        if(it->GetId()==seller.GetId()){

            seller_list_.erase(it);
            return true;
        }
        
    }
    return false;
}

bool Market::AddProductSeller(Product p, std::string id_seller){
    for(auto it=seller_list_.begin() ; it!=seller_list_.end() ; ++it){
            if(it->GetId()==id_seller){
                it->AddProduct(p);
                return true;
            }
    }
    return false;
}

bool Market::AddProductClient(Product p, std::string id_client){
    for(auto it=client_list_.begin() ; it!=client_list_.end() ; ++it){
        if(it->GetId()==id_client){
            for(auto sus=seller_list_.begin() ; sus!=seller_list_.end() ; ++sus){
                std::list<Product> cesta= sus->GetBasket();
                for(auto oc=cesta.begin() ; oc!=cesta.end() ; ++oc){
                    if(oc->GetId()==p.GetId()){
                        Product producto(oc->GetId(), oc->GetName(), oc->GetPrice(), oc->GetMaker(), oc->GetSeller());
                        std::cout<<"|||Cambios en la cesta de "<<it->GetId()<<"|||\n\n";
                        it->AddProduct(producto);
                        std::cout<<"|||Cambios en el stock de "<<sus->GetId()<<"|||\n\n";
                        sus->DeleteProduct(producto);
                        return true;
                    }
                }
            }
            return false;
        }
        
    }
    return false;
}

bool Market::DeleteProductSeller(Product p, std::string id_seller){
    for(auto it=seller_list_.begin() ; it!=seller_list_.end() ; ++it){
        if(it->GetId()==id_seller){
            std::vector<std::string> vs= it->GetIds();
                    for(auto a: vs){
                        if(a==p.GetId()){
                            it->DeleteProduct(p);
                            return true;
                        }
                    }
        }
    }
    return false;
}

bool Market::DeleteProductClient(Product p, std::string id_client){
    for(auto it=client_list_.begin() ; it!=client_list_.end() ; ++it){
        if(it->GetId()==id_client){
            std::vector<std::string> vs=it->GetIds();
            for(auto a: vs){
                if(a==p.GetId()){
                    it->DeleteProduct(p);
                    return true;
                }
            }
        }
    }
    return false;
}
    


float Market::GetMoneyInBasket(){
    float dineros=0.0;
    for(auto it=client_list_.begin() ; it!=client_list_.end() ; ++it){
        std::cout<<it->GetId()<<": "<<it->GetTotal()<<"\n";
        dineros+=it->GetTotal();
    }
    return dineros;
}

bool Market::DumpMarket(int outmode){
    if(outmode<0 || outmode>1){
        return false;
    }
std::string cuenta="|-------------------------------------|\n|CLIENT ID  |PRODUCT ID  |PRODUCT QTY |\n";

for(auto it=client_list_.begin() ; it!=client_list_.end() ; ++it){
    std::vector<std::string> vs=it->GetIds();
    std::vector<int> vq=it->GetQs();
    for(int cont=0 ; cont<it->GetSize() ; cont++){
        cuenta += ("|"+ it->GetId() + "\t    |" + vs[cont] + "\t         |" + std::to_string(vq[cont]) + "\t      |\n");
    }
}
cuenta
+="|-------------------------------------|\n";
cuenta+= "|TOTAL: " + std::to_string(GetMoneyInBasket()) + "€\t\t      |\n" 
+ "|-------------------------------------|\n";
    
    
    if(outmode==1){
        
        std::ofstream tienesquepagaresto("ventas.txt");
        if(tienesquepagaresto.is_open()){          
            tienesquepagaresto << cuenta;
            tienesquepagaresto.close();
        }    
        else{
            std::cerr <<"No se pudo abrir el fichero\n";
        }
    }

    if(outmode==0){

        std::cout<<cuenta<<"\n";               
        
    }      
    return true;
    
}







void Market::MostrarClientes(){

    for(auto it=client_list_.begin() ; it!=client_list_.end() ; ++it){
        std::cout<<it->GetId()<<"\n";
    
    }
}


void Market::MostrarVendedores(){
    
    for(auto it=seller_list_.begin() ; it!=seller_list_.end() ; ++it){
        std::cout<<it->GetId()<<"\n";
    
    }   
}


bool Market::MostrarProductos(int mode){
   
    int cont=0;

    if(mode==1){
        for(auto it=seller_list_.begin() ; it!=seller_list_.end() ; ++it){
            std::vector<std::string> vs=it->GetIds();
            for(auto a: vs){
                std::cout<<it->GetId()<<": "<<a<<"\n";
                cont++;


            }
        }    
        if(cont>0){return true;}
        else{return false;}
    }

    else{
              for(auto it=seller_list_.begin() ; it!=seller_list_.end() ; ++it){
            std::vector<std::string> vs=it->GetIds();
            for(auto a: vs){
                
                cont++;


            }
        }    
        if(cont>0){return true;}
        else{return false;}  
    }
}




bool Market::MostrarProductosdeCliente(std::string id_cliente){

    int cont=0;
    for(auto it=client_list_.begin() ; it!=client_list_.end() ; ++it){
        if(it->GetId()==id_cliente){
            std::vector<std::string> vs=it->GetIds();
            for(auto a: vs){
                std::cout<<a<<", ";
                cont++;
            }
            std::cout<<"\n";
            
        }
    }
    if(cont==0){return false;}
    return true;
}