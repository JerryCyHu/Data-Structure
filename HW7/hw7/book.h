//
// Created by huc3 on 10/29/2019.
//

#ifndef HW7_BOOK_H
#define HW7_BOOK_H

#include <vector>
#include <string>
using namespace std;

class book {
public:
    book():name(""),num(0){};
    book(string name, int n):name(name),num(n){};
    string name;//name of the book
    int num;//number of books available
    vector<string> borrowers;//names of borrowers
};


#endif //HW7_BOOK_H
