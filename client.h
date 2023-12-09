#ifndef CLIENT_H
#define CLIENT_H
#include "person.h"
#include "basket.h"

class Client: public Person, public Basket{
    private:
        int premium_;
    public:
        Client(std::string id, std::string name="empty", std::string town="empty", std::string province="empty", std::string country="empty", int age=0, double rank=0.0, int entry_year=0, int premium=0): Person(id, name, town, province, country, age, rank, entry_year){premium_=premium;}
        int GetPremium(){return premium_;}
        void SetPremium(int premium){premium_=premium;}
};

#endif