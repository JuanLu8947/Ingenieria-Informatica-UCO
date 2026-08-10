// person_test.cc: Juan A. Romero
// A sample program demonstrating using Google C++ testing framework.
//
// This sample shows how to write a simple unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized. You may also throw in additional tests as
// needed.

#include <person.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::StartsWith;

TEST(Person, Constructor1) {
  Person p1("XX1", "empty", "empty", "empty", "empty", 0, 0, 0);
  EXPECT_EQ("empty", p1.GetName());
  EXPECT_EQ("empty", p1.GetTown());
  EXPECT_EQ("empty", p1.GetProvince());
  EXPECT_EQ("empty", p1.GetCountry());
  EXPECT_EQ(0, p1.GetAge());
  EXPECT_FLOAT_EQ(0, p1.GetRank());
  EXPECT_EQ(0, p1.GetEntryYear());
}

TEST(Person, Constructor2) {
  Person p1("XX2", "Ana", "Sevilla", "Sevilla", "España", 31, 9.95, 2023);
  EXPECT_EQ("Ana", p1.GetName());
  EXPECT_EQ("Sevilla", p1.GetTown());
  EXPECT_EQ("Sevilla", p1.GetProvince());
  EXPECT_EQ("España", p1.GetCountry());
  EXPECT_EQ(31, p1.GetAge());
  EXPECT_FLOAT_EQ(9.95, p1.GetRank());
  EXPECT_EQ(2023, p1.GetEntryYear());  
}

TEST(Person, Constructor3) {
  Person p1("XX2", "Ana", "Sevilla", "Sevilla", "España", 31, 9.95, -5);
  EXPECT_EQ("Ana", p1.GetName());
  EXPECT_EQ("Sevilla", p1.GetTown());
  EXPECT_EQ("Sevilla", p1.GetProvince());
  EXPECT_EQ("España", p1.GetCountry());
  EXPECT_EQ(31, p1.GetAge());
  EXPECT_FLOAT_EQ(9.95, p1.GetRank());
  EXPECT_EQ(0, p1.GetEntryYear());  
}

TEST(Person, Constructor4) {
  Person p1("XX2", "Ana", "Sevilla", "Sevilla", "España", 31, 9.95, 0);
  EXPECT_EQ("Ana", p1.GetName());
  EXPECT_EQ("Sevilla", p1.GetTown());
  EXPECT_EQ("Sevilla", p1.GetProvince());
  EXPECT_EQ("España", p1.GetCountry());
  EXPECT_EQ(31, p1.GetAge());
  EXPECT_FLOAT_EQ(9.95, p1.GetRank());
  EXPECT_EQ(0, p1.GetEntryYear());  
}

TEST(Person, Modifiers) {
  Person p1("XX2", "Ana", "Sevilla", "Sevilla", "España", 31, 9.95, 2023);
  p1.SetId("XXX7");
  EXPECT_EQ("XXX7", p1.GetId());
  p1.SetName("Andrea");
  EXPECT_EQ("Andrea", p1.GetName());
  p1.SetTown("Córdoba");
  EXPECT_EQ("Córdoba", p1.GetTown());
  p1.SetProvince("Córdoba");
  EXPECT_EQ("Córdoba", p1.GetProvince());
  p1.SetCountry("Francia");
  EXPECT_EQ("Francia", p1.GetCountry());
  p1.SetAge(50);
  EXPECT_EQ(50, p1.GetAge());
  p1.SetRank(7.77);
  EXPECT_FLOAT_EQ(7.77, p1.GetRank());
  p1.SetEntryYear(2021);
  EXPECT_EQ(2021, p1.GetEntryYear());  
}

TEST(Person, SetAge) {
  Person p1("XX2", "Ana", "Sevilla", "Sevilla", "España", 31, 9.95, 2023);
  EXPECT_TRUE(p1.SetAge(21));
  EXPECT_EQ(21, p1.GetAge());
  EXPECT_FALSE(p1.SetAge(0));
  EXPECT_EQ(21, p1.GetAge());
  EXPECT_FALSE(p1.SetAge(-6));
  EXPECT_EQ(21, p1.GetAge());  

}

TEST(Person, SetEntryYear) {
  Person p1("XX2", "Ana", "Sevilla", "Sevilla", "España", 31, 9.95, 2023);
  EXPECT_TRUE(p1.SetEntryYear(2021));
  EXPECT_EQ(2021, p1.GetEntryYear());
  EXPECT_FALSE(p1.SetEntryYear(2000));
  EXPECT_EQ(2021, p1.GetEntryYear());
  EXPECT_FALSE(p1.SetEntryYear(1));
  EXPECT_EQ(2021, p1.GetEntryYear());  

}

TEST(Person, GetDataStr) {
  Person p1("778", "Ana", "Sevilla", "Sevilla", "España", 31, 9.95, 2023);
  EXPECT_THAT(p1.GetDataStr(), StartsWith("Person:\nid: 778\nname: Ana\n"
                                           "town: Sevilla\n"
                                           "province: Sevilla\n"
                                           "country: España\n"
                                           "age: 31\n"
                                           "rank: 9.950000\n"
                                           "entry_year: 2023\n"
                                           ));
}


TEST(Person, Get_AddPreference) {
  Person p1("XX1", "empty", "empty", "empty", "empty", 0, 0, 0);
  std::vector<std::string> v;
  p1.AddPreferences("surf");
  v=p1.GetPreferences();
  EXPECT_EQ(1, v.size());
  EXPECT_EQ("surf", v[0]);
  p1.AddPreferences("golf");
  v=p1.GetPreferences();
  EXPECT_EQ(2, v.size());
  EXPECT_EQ("surf", v[0]);  
  EXPECT_EQ("golf", v[1]);  
}

TEST(Person, AddPreferences) {
  Person p1("XX1", "empty", "empty", "empty", "empty", 0, 0, 0);
  std::vector<std::string> v;
  p1.AddPreferences("surf", "padel", "rock");
  v=p1.GetPreferences();
  EXPECT_EQ(3, v.size());
  EXPECT_EQ("surf", v[0]);
  EXPECT_EQ("padel", v[1]);
  EXPECT_EQ("rock", v[2]);
  p1.AddPreferences("golf", "cinema", "music");
  v=p1.GetPreferences();
  EXPECT_EQ(6, v.size());
  EXPECT_EQ("golf", v[0]);
  EXPECT_EQ("surf", v[1]);
  EXPECT_EQ("cinema", v[2]);
  EXPECT_EQ("padel", v[3]);
  EXPECT_EQ("rock", v[4]);
  EXPECT_EQ("music", v[5]);
}

TEST(Person, ChangePreference) {
  Person p1("XX1", "empty", "empty", "empty", "empty", 0, 0, 0);
  std::vector<std::string> v;
  p1.AddPreferences("surf");
  v=p1.GetPreferences();
  EXPECT_EQ(1, v.size());
  EXPECT_EQ("surf", v[0]);
  p1.AddPreferences("golf");
  v=p1.GetPreferences();
  EXPECT_EQ(2, v.size());
  EXPECT_EQ("surf", v[0]);  
  EXPECT_EQ("golf", v[1]);  
}

TEST(Person, ShowPreferences) {
  Person p1("XX1", "empty", "empty", "empty", "empty", 0, 0, 0);
  p1.AddPreferences("surf");
  p1.AddPreferences("golf");
  p1.AddPreferences("fashion", "padel", "rock");
  p1.AddPreferences("futbol", "cinema", "music");
  p1.ShowPreferences();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}