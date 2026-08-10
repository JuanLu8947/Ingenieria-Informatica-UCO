#include "person.h"

int main(){
    std::string id, name,town,province,country;
    int age,entry_year;
    double rank;

    //Person
    std::cout << "Persona 1:\n"
              << "id: ";
    std::cin >> id;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "town: ";
    std::cin >> town;
    std::cout << "province: ";
    std::cin >> province;
    std::cout << "country: ";
    std::cin >> country;
    std::cout << "age: ";
    std::cin >> age;
    std::cout << "entry_year: ";
    std::cin >> entry_year;
    std::cout << "rank: ";
    std::cin >> rank;
    Person p1(id, name, town, province, country, age, rank, entry_year);
    std::cout << "\n" << p1.GetDataStr();

    //Person
    std::cout << "\n\nPersona 2:\n"
              << "id: ";
    std::cin >> id;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "town: ";
    std::cin >> town;
    std::cout << "province: ";
    std::cin >> province;
    std::cout << "country: ";
    std::cin >> country;
    std::cout << "age: ";
    std::cin >> age;
    std::cout << "entry_year: ";
    std::cin >> entry_year;
    std::cout << "rank: ";
    std::cin >> rank;
    Person p2(id, name, town, province, country, age, rank, entry_year);
    std::cout << "\n" << p2.GetDataStr();
}