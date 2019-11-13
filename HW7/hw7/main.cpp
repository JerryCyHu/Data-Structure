#include <iostream>
#include <map>
#include <cassert>
#include <string>
#include "book.h"

// two data structures store all of the information for efficiency
typedef map<string,book> LIBRARY_TYPE;
typedef map<string,vector<string> > PEOPLE_TYPE;


// prototypes for the helper functions
void addItem(LIBRARY_TYPE& library);
void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void lookup(LIBRARY_TYPE& library);
void printPeople(PEOPLE_TYPE& people);


int main() {
    freopen("input3.txt", "r", stdin);
    freopen("output3.txt", "w", stdout);
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
  if(library.find(title) != library.end()){//already has this book in database
      library[title].num+=num;
  } else{//first time see this book
      library[title].name = title;
      library[title].num = num;
  }
  if (num > 1){
      cout<<"added " <<num <<" copies of " <<title <<endl;
  } else{
      cout<<"added " <<num <<" copy of " <<title <<endl;
  }
}


void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  std::string title;
  std::cin >> name >> title;
  //check the name in people map:
  if (people.find(name) != people.end()) {//there is that person
      //check if the person already own the book
      bool owned = false;
      for (int i = 0; i < people[name].size(); ++i) {
          if (people[name][i] == title)
              owned = true;
      }
      if (owned) {//the person already owned the book
          cout << name << " already has " << title <<endl;
          return;
      }
  }
  if (library.find(title) != library.end()) {//there should has this book
      if (library[title].num > 0) {//there are books left to be lended
          library[title].num--;
          library[title].borrowers.push_back(name);
          people[name].push_back(title);
          cout << name << " checked out " << title <<endl;
      } else {//no book left
          cout << "no copies of " << title << " available" <<endl;
      }
  } else {
      cout <<"don't have " <<title <<" in library" <<endl;
  }




}


void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  std::cin >> name;
  vector<string>& p = people[name];
  if (p.size() != 0) {//the person did borrow something
      for (int i = 0; i < p.size(); ++i) {
          library[p[i]].num++;
          for (int j = 0; j < library[p[i]].borrowers.size(); ++j) {
              if (library[p[i]].borrowers[j] == name){
                  library[p[i]].borrowers.erase(library[p[i]].borrowers.begin()+j);
                  break;
              }
          }
      }
      int num = p.size();
      if (num > 1){
          cout<<name <<" returned " <<num <<" items" <<endl;
      } else{
          cout<<name <<" returned " <<num <<" item" <<endl;
      }
      p.clear();
  }else {
      cout<<name << " has no items checked out" <<endl;
  }

}


void lookup(LIBRARY_TYPE& library) {
  std::string title;
  std::cin >> title;

  if (library.find(title) != library.end()){//book exist
      cout<<"library info for: " <<title <<endl;

      int num = library[title].num;
      if (num > 1){
          cout<<"  " <<num <<" copies available" <<endl;
      } else if (num == 1) {
          cout<<"  " <<num <<" copy available" <<endl;
      }

      num = library[title].borrowers.size();
      if (num > 1){
          cout<<"  " <<num <<" copies checked out by:" <<endl;
          for (int i = 0; i < library[title].borrowers.size(); ++i) {
              cout<<"    " <<library[title].borrowers[i] <<endl;
          }
      } else if (num == 1){
          cout<<"  " <<num <<" copy checked out by:" <<endl;
          cout<<"    " <<library[title].borrowers[0] <<endl;
      }
  }else {
      cout <<"don't have " <<title <<" in library!" <<endl;
  }





}


void printPeople(PEOPLE_TYPE& people) {
    for (PEOPLE_TYPE::iterator itr = people.begin(); itr != people.end(); ++itr) {
        bool needToDisplay = false;//if no book checked out then this person is no need to be displayed
        if (itr->second.size() > 1) {
            cout <<itr->first << " has these items checked out:"<<endl;
            needToDisplay = true;
        } else if (itr->second.size() == 1){
            cout <<itr->first << " has this item checked out:"<<endl;
            needToDisplay = true;
        }

        if (needToDisplay){
            for (int i = 0; i < itr->second.size(); ++i) {
                cout<<"  " <<itr->second[i] <<endl;
            }
        }
    }





}
