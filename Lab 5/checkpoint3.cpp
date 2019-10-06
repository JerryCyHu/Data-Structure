#include <iostream>
#include <string>
using namespace std;

// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 10.
template <class T>
class Node {
public:
  T value;
  Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL) {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}



template <class T>
void reverse(Node<T>* &input) {

  // FILL IN THIS FUNCTION
	T v;
	int size = 0;
	Node<T>*list = input;
	while (size == 0||list != NULL) {
		list = list->ptr;
		size++;
	}
	Node<T>*list1 = input;
	Node<T>*list2 = input;
	int s = size / 2;
	int conS = size;
	while (s > 0) {
		list1 = input;
		list2 = input;
		int s1 = size;
		int s2 = size;
		while (s1 > 1) {
			list1 = list1->ptr;
			s1--;
		}
		while (s2 < conS)
		{
			list2 = list2->ptr;
			s2++;
		}
		v = list1->value;
		list1->value = list2->value;
		list2->value = v;
		s--;
		size--;
	}

}




int main() {

  // manually create a linked list of notes with 4 elements
  Node<int>* my_list = new Node<int>; 
  my_list->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  my_list->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->value = 3;
  my_list->ptr->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->ptr->value = 4;
  my_list->ptr->ptr->ptr->ptr = NULL;

  
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");


  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in lecture 10.

}

// ===========================================================================
