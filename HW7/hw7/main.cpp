#include <iostream>
#include <map>
#include <cassert>
#include <string>


// two data structures store all of the information for efficiency
typedef ? LIBRARY_TYPE;
typedef ? PEOPLE_TYPE;


// prototypes for the helper functions
void addItem(LIBRARY_TYPE& library);
void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void lookup(LIBRARY_TYPE& library);
void printPeople(PEOPLE_TYPE& people);


int main() {
  LIBRARY_TYPE library;
  PEOPLE_TYPE people;
  char c;
  while (std::cin >> c) {
    if (c == 'a') {
      addItem(library);
    } else if (c == 'c') {
      checkoutItem(library,people);
    } else if (c == 'r') {
      returnItems(library,people);
    } else if (c == 'l') {
      lookup(library);
    } else if (c == 'p') {
      printPeople(people);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}


void addItem(LIBRARY_TYPE& library) {
  std::string title;
  int num;
  std::cin >> num >> title;






}


void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  std::string title;
  std::cin >> name >> title;





}


void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  std::cin >> name;





}


void lookup(LIBRARY_TYPE& library) {
  std::string title;
  std::cin >> title;






}


void printPeople(PEOPLE_TYPE& people) {






}
