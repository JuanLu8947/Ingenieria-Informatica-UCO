#include "person.h"

int main(){

    std::string id,name,town,province,country;
    int age,entry_year;
    double rank;

    std::cout << "id: " << "\n";
    std::cin >> id;
    std::cout << "name: " << "\n";
    std::cin >> name;
    std::cout << "town: " << "\n";
    std::cin >> town;
    std::cout << "province: " << "\n";
    std::cin >> province;
    std::cout << "country" << "\n";
    std::cin >> country;
    std::cout << "age" << "\n";
    std::cin >> age;
    std::cout << "entry_year" << "\n";
    std::cin >> entry_year;
    std::cout << "rank" << "\n";
    std::cin >> rank;
    
    Person p1(id, name, town, province, country, age, rank, entry_year);


    std::cout << "id: " << "\n";
    std::cin >> id;
    std::cout << "name: " << "\n";
    std::cin >> name;
    std::cout << "town: " << "\n";
    std::cin >> town;
    std::cout << "province: " << "\n";
    std::cin >> province;
    std::cout << "country" << "\n";
    std::cin >> country;
    std::cout << "age" << "\n";
    std::cin >> age;
    std::cout << "entry_year" << "\n";
    std::cin >> entry_year;
    std::cout << "rank" << "\n";
    std::cin >> rank;
    Person p2(id, name, town, province, country, age, rank, entry_year);

    
    p1.GetDataStr();
    p2.GetDataStr();
}