#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include <vector>

class Person{
    private:
        std::string name_, id_, town_, province_, country_;
        int age_, entry_year_;
        double rank_;
        std::vector<std::string> preferences_;
    public: 
        Person(std::string id, std::string name, std::string town, std::string province, std::string country, int age, double rank, int entry_year);
        std::string GetId(){return id_;}
        std::string GetTown(){return town_;}
        std::string GetProvince(){return province_;}
        std::string GetCountry(){return country_;}
        int GetEntryYear(){return entry_year_;}
        void SetId(std::string id){id_=id;}
        void SetName(std::string name){name_=name;}
        void SetTown(std::string town){town_=town;}
        void SetProvince(std::string province){province_=province;}
        void SetCountry(std::string country){country_=country;}
        bool SetAge(int age){
            if(age>0){
                age_=age;
                return true;
            }
            return false;
        }
        void SetRank(double rank){rank_=rank;}
        bool SetEntryYear(int entry_year){
            if(entry_year>2000){
                entry_year_=entry_year;
                return true;
            }
            return false;
        }
        
        std::string GetName(){return name_;}
        int GetAge(){return age_;}
        double GetRank(){return rank_;}

        std::string GetDataStr(){
            std::string Pe="Person:\n";
            Pe += 
            "id: " + id_ + "\n" + 
            "name: " + name_ + "\n" + 
            "town: " + town_ + "\n" + 
            "province: " + province_ + "\n" + 
            "country: " + country_ + "\n" + 
            "age: " + std::to_string(age_)+ "\n" + 
            "rank: " + std::to_string(rank_) + "\n" + 
            "entry_year: " + std::to_string(entry_year_) + "\n";
            return Pe;
        }

        std::vector<std::string>GetPreferences();
        void AddPreferences(std::string s1);
        void AddPreferences(std::string s1, std::string s2, std::string s3);
        void ShowPreferences();
        void ChangePreference(int n, std::string c);

};
#endif