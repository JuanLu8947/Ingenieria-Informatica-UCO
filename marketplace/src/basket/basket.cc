#include "basket.h"

void Basket::AddProduct(Product p){
    if(product_quantity_.count(p.GetId()) == 0){
        product_list_.push_back(p);
        product_quantity_[p.GetId()] =1;
    }
    else{
        product_quantity_[p.GetId()]++;
    }
    total_ += p.GetPrice();
}

bool Basket::DeleteProduct(Product p){
    return DeleteProduct(p.GetId());
} 

bool Basket::DeleteProduct(std::string id){
    if (product_quantity_.count(id) == 0) {
        return false;
    }
    std::list<Product>::iterator pos;//iterator
    for(pos = product_list_.begin(); pos != product_list_.end(); ++pos){//comprobamos si existe el producto en la cesta
        if((*pos).GetId() == id) break; //si existe, sale del bucle, y pos hara referencia a en que parte de la lista se encuentra; sino, pos sera .end()
    }
    if(pos == product_list_.end()){ //si llega al final de la lista se para
        return false;
    }
    else{ //Practicamente igual que la anterior pero saca la info del producto de product_list_, por lo que cambia el total_ antes de borrarlo
        total_ -= (*pos).GetPrice(); //total disminuye según el precio del producto
        if((product_quantity_[id] -= 1) <= 0){ //hay un producto menos pero no menor de 0
            product_list_.erase(pos);
            product_quantity_.erase(id);
        }
        return true;
    }
}

void Basket::DeleteBasket(){
    product_list_.clear();
    product_quantity_.clear();
    total_ = 0.0;
}

int Basket::GetSize(){
    return product_list_.size();
}

float Basket::GetTotal(){
    return total_;
}

std::vector<std::string> Basket::GetIds(){
    std::vector<std::string> id_v;
    if(product_list_.size() == 0) return id_v; //Si la cesta/lista esta vacia, devolvera un vector vacio
    else{
        std::list<Product>::iterator pos;
    for(pos = product_list_.begin(); pos != product_list_.end();pos++){
        id_v.push_back((*pos).GetId()); //Se asigna el id correspondiente a la posicion del iterador al vector
    } //con push_back se va añadiendo al final de vector id, los ids
    return id_v;
    }
}

std::vector<int> Basket::GetQs(){
    std::vector<int> quantity_v;
    if(product_list_.size() == 0) return quantity_v; //Si la cesta/lista esta vacia, devolvera un vector vacio
    else{
        std::map<std::string, int>::iterator pos;
        for(pos = product_quantity_.begin(); pos != product_quantity_.end();pos++){
            quantity_v.push_back((*pos).second); //Se asigna la cantidad correspondiente a la posicion del iterador al vector
        } //con push_back se va añadiendo al final de vector cant, los ids
        return quantity_v;        ///second = key
    }
}