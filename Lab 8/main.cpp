#include <iostream>
#include <map>
#include <fstream>

using namespace std;

void hahaha(string& str){
    ifstream file(str);
    map<int, int> a_map;
    int c = 0;
    while (file >> c) {
        ++a_map[c];
    }
    ////////find////
    int biggest = 0;
    for (map<int, int>::iterator itr = a_map.begin(); itr != a_map.end(); ++itr) {
        if (biggest < itr->second)
            biggest = itr->second;
    }
    cout<<endl<<"Mode(s) is(are)";
    for (map<int, int>::iterator itr = a_map.begin(); itr != a_map.end(); ++itr) {
        if (biggest == itr->second)
            cout<<" "<<itr->first;
    }
}

void hehehe(string& str){
    ifstream file(str);
    map<int, int> a_map;
    int c = 0;
    while (file >> c) {
        if (a_map.find(c) != a_map.end()){
            int value = a_map.find(c)->second+1;
            a_map.erase(a_map.find(c));
            a_map.insert(pair<int,int>(c,value));
        }else{
            a_map.insert(pair<int,int>(c,1));
        }
    }
    ////////////////////find.///////////////
    int biggest = 0;
    for (map<int, int>::iterator itr = a_map.begin(); itr != a_map.end(); ++itr) {
        if (biggest<itr->second)
            biggest = itr->second;
    }
    cout<<endl<<"Mode(s) is(are)";
    for (map<int, int>::iterator itr = a_map.begin(); itr != a_map.end(); ++itr) {
        if (biggest == itr->second)
            cout<<" "<<itr->first;
    }
}

int main(int argc, char* argv[]) {
    string str = argv[1];
    //hahaha(str);
    hehehe(str);
    return 0;
}