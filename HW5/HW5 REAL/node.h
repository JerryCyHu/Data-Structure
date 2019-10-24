#ifndef __node_h_
#define __node_h_
#include <string>
using namespace std;

class Node
{
public:
	Node() {};
	Node(const string& v) : value_(v), next_(NULL), prev_(NULL), backup_next_(NULL), backup_prev_(NULL), added_(false), removed_(false)  {}
	~Node() {};

	Node* next_;
	Node* prev_;
	Node* backup_next_;
	Node* backup_prev_;
	string value_;
	bool added_;//whether it is added
	bool removed_;//whether it is removed

	void debug() const;

private:

};

#endif

