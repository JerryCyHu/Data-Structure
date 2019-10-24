#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include "essay.h"
using namespace std;

void Essay::push_front(string str) {
	if (tail_ == NULL && head_ == NULL) {
		Node* newHead_ = new Node(str);
		newHead_->added_ = true;
		tail_ = newHead_;
		head_ = newHead_;
	}
	else
	{
		Node* newHead_ = new Node(str);
		newHead_->added_ = true;
		head_->prev_ = newHead_;
		newHead_->next_ = head_;
		head_ = newHead_;
	}
	size_++;
}

void Essay::push_back(string str) {
	if (tail_ == NULL && head_ == NULL) {
		Node* newTail_ = new Node(str);
		newTail_->added_ = true;
		tail_ = newTail_;
		head_ = newTail_;
	}
	else
	{
		Node* newTail_ = new Node(str);
		newTail_->added_ = true;
		tail_->next_ = newTail_;
		newTail_->prev_ = tail_;
		tail_ = newTail_;
	}
	size_++;
}

Essay::iterator Essay::begin() {
	return iterator(head_,false);
}

Essay::iterator Essay::end() {
	return iterator(NULL,false);
}

Essay::iterator Essay::backup_begin() {
	
	return iterator(backup_head_,true);
}

Essay::iterator Essay::backup_end() {
	
	return iterator(NULL,true);
}

int Essay::size() {
	return size_;
}

void Essay::pop_front() {

	if (size_ > 0)
	{
		bool deleteOrNot = false;

		if (head_->backup_next_ == NULL && head_->backup_prev_ == NULL)
			deleteOrNot = true;

		Node* d = head_;

		iterator itr = begin();
		itr.ptr_->removed_ = true;
		head_ = itr.ptr_->next_;
		head_->prev_ = NULL;
		
		d->next_ = NULL;
		d->prev_ = NULL;

		size_--;

		if(deleteOrNot == true)
			delete d;
	}
	else
	{
		cerr << "No content in the essay";
	}
}

void Essay::pop_back() {
	if (size_ > 0)
	{
		bool deleteOrNot = false;

		if (tail_->backup_next_ == NULL && tail_->backup_prev_ == NULL)
			deleteOrNot = true;

		Node* d = tail_;

		iterator itr = tail_;
		itr.ptr_->removed_ = true;
		tail_ = itr.ptr_->prev_;
		tail_->next_ = NULL;

		d->next_ = NULL;
		d->prev_ = NULL;

		size_--;

		if (deleteOrNot == true)
			delete d;
	}
	else
	{
		cerr << "No content in the essay";
	}
}

Essay::iterator Essay::insert(iterator i, string s) {
	Node* n = new Node(s);
	n->added_ = true;
	Node* p = i.ptr_;
	--i;
	(i).ptr_->next_ = n;
	n->prev_ = (i).ptr_;
	n->next_ = p;
	p->prev_ = n;
	i++;
	size_++;
	return i;
}

Essay::iterator Essay::erase(iterator i) {
	bool deleteOrNot = false;

	if (i.ptr_->backup_next_ == NULL && i.ptr_->backup_prev_ == NULL) 
		deleteOrNot = true;

	Node* d = i.ptr_;
	i.backup_ = false;
	i.ptr_->removed_ = true;
	size_--;
	Node* n = (++i).ptr_;
	--i;
	--i;
	i.ptr_->next_ = n;
	n->prev_ = i.ptr_;
	d->next_ = NULL;
	d->prev_ = NULL;

	if (deleteOrNot == true)
		delete d;

	return ++i;
}

void Essay::revert() {
	iterator i = iterator(head_);
	while (i.ptr_ != NULL)
	{
		Node* tempN = i.ptr_->next_;
		if (i.ptr_->added_ == true) {
			delete i.ptr_;
		}
		i.ptr_ = tempN;
	}
	i = iterator(backup_head_);
	i.backup_ = true;
	for (i; i != end();i++) {
		i.ptr_->next_ = i.ptr_->backup_next_;
		i.ptr_->prev_ = i.ptr_->backup_prev_;
		i.ptr_->added_ = false;
		i.ptr_->removed_ = false;
	}
	head_ = backup_head_;
	tail_ = backup_tail_;
	size_ = backup_size_;
}

int Essay::num_removed() {
	int sum = 0;
	iterator i = backup_begin();
	i.backup_ = true;
	for (i; i != end(); i++) {
		if (i.ptr_->removed_ == true)
		{
			sum++;
		}
	}
	return sum;
}

int Essay::num_added() {
	int sum = 0;
	iterator i = begin();
	i.backup_ = false;
	for (i; i != end(); i++) {
		if (i.ptr_->added_ == true)
		{
			sum++;
		}
	}
	return sum;
}

void Essay::backup() {
	iterator i = iterator(backup_head_);
	i.backup_ = true;
	while (i.ptr_ != NULL)
	{
		Node* tempN = i.ptr_->backup_next_;
		if (i.ptr_->removed_ == true) {
			delete i.ptr_;
		}
		i.ptr_ = tempN;
	}
	i = iterator(head_);
	i.backup_ = false;
	for (i; i != end();i++) {
		i.ptr_->backup_next_ = i.ptr_->next_;
		i.ptr_->backup_prev_ = i.ptr_->prev_;
		i.ptr_->added_ = false;
		i.ptr_->removed_ = false;
	}
	backup_head_ = head_;
	backup_tail_ = tail_;
	backup_size_ = size_;
}

bool Essay::splice(iterator iBegin, iterator iEnd, iterator iDestination) {
	for (iterator i = iBegin; i != ++iEnd; i++)
	{
		insert(iDestination, *i);
	}
	for (iterator i = iBegin; i != ++iEnd; i++)
	{
		erase(i);
	}
	return true;
}