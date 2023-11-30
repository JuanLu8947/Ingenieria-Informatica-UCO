#include "market.h"

bool Market::AddClient(Client client){
    std::list<Client>::iterator pos;//iterator
    for(pos = client_list_.begin(); pos != client_list_.end(); ++pos){
        if((*pos).GetId() == client.GetId()) return false;
    }
    client_list_.push_back(client);
    return true;
}

bool Market::AddSeller(Seller seller){
    std::list<Seller>::iterator pos;//iterator
    for(pos = seller_list_.begin(); pos != seller_list_.end(); ++pos){
        if((*pos).GetId() == seller.GetId()) return false;
    }
    seller_list_.push_back(seller);
    return true;
}

bool Market::DeleteClient(Client client){
    std::list<Client>::iterator pos;//iterator
    for(pos = client_list_.begin(); pos != client_list_.end(); ++pos){
        if((*pos).GetId() == client.GetId()){
            client_list_.erase(pos);
            return true;
        }
    }
    return false;
}

bool Market::DeleteSeller(Seller seller){
    std::list<Seller>::iterator pos;//iterator
    for(pos = seller_list_.begin(); pos != seller_list_.end(); ++pos){
        if((*pos).GetId() == seller.GetId()){
            seller_list_.erase(pos);
            return true;
        }
    }
    return false;
}

bool Market::AddProductSeller(Product p, std::string id_seller){
    std::list<Seller>::iterator pos;//iterator
    for(pos = seller_list_.begin(); pos != seller_list_.end(); ++pos){
        if((*pos).GetId() == id_seller){
            (*pos).AddProduct(p);
            return true;
        }
    }
    return false;
}

bool Market::AddProductClient(Product p, std::string id_client){
    std::list<Client>::iterator pos;//iterator
    std::list<Seller>::iterator it;//iterator
    for(it = seller_list_.begin(); it != seller_list_.end(); ++it){
        if((*it).DeleteProduct(p) == true){
            for(pos = client_list_.begin(); pos != client_list_.end(); ++pos){
                if((*pos).GetId() == id_client){
                    //std::vector<std::string> v = (*it).GetIds();
                    //for(auto i : v){
                        //if(i==(*pos).GetId()){
                            (*pos).AddProduct(p); //añado client
                            return true;
                        //}
                    //}
                } 
            }
        }
    }
    return false;
}

bool Market::DeleteProductSeller(Product p, std::string id_seller){
    std::list<Seller>::iterator pos;//iterator
    for(pos = seller_list_.begin(); pos != seller_list_.end(); ++pos){
        if((*pos).GetId() == id_seller){
            if((*pos).DeleteProduct(p) == true){
                return true;
            }
            else{
                return false;
            }
        }
    }
    return false;
}

bool Market::DeleteProductClient(Product p, std::string id_client){
    std::list<Client>::iterator pos;//iterator
    for(pos = client_list_.begin(); pos != client_list_.end(); ++pos){
        if((*pos).GetId() == id_client){
            if((*pos).DeleteProduct(p) == true){
                return true;
            }
            else{
                return false;
            }
        }
    }
    return false;
}

float Market::GetMoneyInBasket(){
    float suma=0.0;
    std::list<Client>::iterator pos;//iterator
    for(pos = client_list_.begin(); pos != client_list_.end(); ++pos){
        suma+= (*pos).GetTotal();
    }
    return suma;
}

bool Market::DumpMarket(int outmode){
    std::list<Client>::iterator pos;
    std::vector<std::string> idprod;
    std::vector<int> qprod;
    if(outmode<0 || outmode>1) return false;
    else{
        if(outmode==1){
            std::ofstream fich("ventas.txt");
            if(fich.is_open()){
                fich << "|-------------------------------------|\n" 
                     << "|CLIENT ID  |PRODUCT ID  |PRODUCT QTY |\n";
                for(pos = client_list_.begin(); pos != client_list_.end(); ++pos){ 
                    idprod = (*pos).GetIds();
                    qprod = (*pos).GetQs();
                    for(int i=0; i < (*pos).GetSize(); i++){
                        fich << "|" << (*pos).GetId() << "         |" 
                             << idprod[i]      << "          |" 
                             << qprod[i]       << "           |\n";
                    }
                }
                fich << "|-------------------------------------|\n" 
                     << "|TOTAL: " << GetMoneyInBasket() << "€                          |\n" 
                     << "|-------------------------------------|";
                fich.close();
            }
            else std::cout << "Error de apertura del fichero";
        }
        if(outmode==1){
            std::cout << "|-------------------------------------|\n" 
                 << "|CLIENT ID  |PRODUCT ID  |PRODUCT QTY |\n";
            for(pos = client_list_.begin(); pos != client_list_.end(); ++pos){ 
                    idprod = (*pos).GetIds();
                    qprod = (*pos).GetQs();
                    for(int i=0; i < (*pos).GetSize(); i++){
                        std::cout << "|" << (*pos).GetId() << "         |" 
                             << idprod[i]      << "          |" 
                             << qprod[i]       << "           |\n";
                    }
            }
            std::cout << "|-------------------------------------|\n" 
                 << "|TOTAL: " << GetMoneyInBasket() << "€                          |\n" 
                 << "|-------------------------------------|";
        }
    }
    return true;
}

// f(x) necesarias para app
void Market::muestraC(){
    std::list<Client>::iterator pos;
    for(pos = client_list_.begin() ; pos != client_list_.end() ; ++pos)
        std::cout << (*pos).GetId() << "\n";
}
void Market::muestraV(){
    std::list<Seller>::iterator pos;
    for(pos = seller_list_.begin() ; pos != seller_list_.end() ; ++pos)
        std::cout << (*pos).GetId() << "\n";
}

void Market::muestraP(){
    std::list<Seller>::iterator pos;
    for(auto pos=seller_list_.begin() ; pos!=seller_list_.end() ; ++pos){
        std::vector<std::string> v = (*pos).GetIds();
        for(auto i: v)
            std::cout<< "Vendedor: " <<(*pos).GetId() << ". Id de producto: "<< i << "\n";
    }
}

bool Market::muestraClient(std::string client_id){
    std::list<Client>::iterator pos;
    for(pos = client_list_.begin() ; pos != client_list_.end() ; ++pos)
        if((*pos).GetId()==client_id) return true;
    return false;
}

bool Market::muestraSeller(std::string seller_id){
    std::list<Seller>::iterator pos;
    for(pos = seller_list_.begin() ; pos != seller_list_.end() ; ++pos)
        if((*pos).GetId()==seller_id) return true;
    return false;
}