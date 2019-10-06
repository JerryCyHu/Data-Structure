#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
template <class T>
void print(list<T> &data, const string &label) {
  std::cout << label << " ";
  for (typename list<T>::iterator itr = data.begin(); itr != data.end(); itr++) {
    cout << " " << *itr;
  }
  cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {
	typename list<T>::reverse_iterator ritr = data.rbegin();
	int size = 0;
	
		for (typename list<T>::iterator itr = data.begin(); itr != data.end(); itr++) {
			size++;
		}
		typename list<T>::iterator it = data.end();
		for (int i = 0; i < size; i++) {
			data.insert(it, data.front());
			it--;
			data.pop_front();
		}

  // FILL IN THIS FUNCTION
  
}


int main() {
  std::list<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");
}
