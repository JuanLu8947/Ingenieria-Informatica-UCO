#include "person.h"

std::vector <std::string> Person::GetPreferences(){
    return preferences_;
}

void Person::AddPreferences(std::string s1){
    preferences_.push_back(s1);
}

void Person::AddPreferences(std::string s1, std::string s2, std::string s3){
    preferences_.insert(preferences_.begin(), s1);
    preferences_.insert(preferences_.end(), s3);
    preferences_.insert(preferences_.begin()+(preferences_.size()/2), s2);
}

void Person::ShowPreferences(){
    std::cout << "\nLas preferencias son: " << std::endl;
    for (auto s: preferences_){
        std::cout << s << std::endl;
    }
}

void Person::ChangePreference(int n, std::string c){
    try{
        preferences_.at(n) = c;
    }
    catch (std::out_of_range const& exc){
        std::cout << exc.what() << "\n";
    }
}

Person::Person(std::string id, std::string name, std::string town, std::string province, std::string country, int age, double rank, int entry_year){
    id_=id;
    name_=name;
    town_=town;
    province_=province;
    country_=country;
    age_=age;
    rank_=rank;
                        
    name= "empty";
    town = "empty";
    province = "empty";
    country = "empty";
    age= 0;
    rank= 0;
    if(entry_year > 2000){
        entry_year_=entry_year;
    }
    else{entry_year=0; entry_year_=entry_year;}
}