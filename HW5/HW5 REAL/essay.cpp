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

//push element to the head. set added to true
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

//push back and set added to true
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
//get Begin
Essay::iterator Essay::begin() {
    return iterator(head_,false);
}
Essay::iterator Essay::getbegin() const {
    return iterator(head_,false);
}

//get end
Essay::iterator Essay::end() {
	return iterator(NULL,false);
}
Essay::iterator Essay::getend() const {
    return iterator(NULL,false);
}

//get back begin, set backup_ to true
Essay::iterator Essay::backup_begin() {
	
	return iterator(backup_head_,true);
}
Essay::iterator Essay::getbackup_begin() const {

    return iterator(backup_head_,true);
}

//get back up end, set backup_ to true
Essay::iterator Essay::backup_end() {
	
	return iterator(NULL,true);
}
Essay::iterator Essay::getbackup_end() const {

    return iterator(NULL,true);
}

//get the size of list
int Essay::size() {
	return size_;
}

//delete from front
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

//delete from bottom.
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

//insert to iterator's left
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

//erase and set the non backup properties to null;
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

//revert it to backup version. added and removed must be false
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

//number of nodes removed
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

//number of nodes added
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

//backup stuff
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

//helper function to splice. cut the nodes
Essay::iterator Essay::spliceCut(iterator i){
    Node* d = i.ptr_;
    iterator itr = i;
    size_--;
    Node* n = (++i).ptr_;
    --i;
    --i;
    i.ptr_->next_ = n;
    n->prev_ = i.ptr_;
    d->next_ = NULL;
    d->prev_ = NULL;
    return itr;
}

//helper funciton to splice, paste the nodes
Essay::iterator Essay::splicePaste(iterator content, iterator i){
    Node* n = content.ptr_;
    Node* p = i.ptr_;
    --i;
    (i).ptr_->next_ = n;
    n->prev_ = (i).ptr_;
    n->next_ = p;
    p->prev_ = n;
    i++;
    size_++;
    return content;
}

//cut and paste, no node and or deleted
bool Essay::splice(iterator iBegin, iterator iEnd, iterator iDestination) {
    /////check avalability////////
    bool avalable1 = false;
    for(iterator i = iBegin; i != end();i++){
        if (i == iEnd) {
            avalable1 = true;
            break;
        }
    }
    bool avalable2 = true;
    for(iterator i = iDestination; i != end();i++){
        if(i == iBegin){
            break;
        }
        if (i == iEnd) {
            avalable2 = false;
            break;
        }
    }
    /////////////////////////////
    if(avalable1&&avalable2) {
        Node *endNode = iEnd.ptr_;
        for (iterator i = iBegin; i != endNode;) {
            iterator ii = ++i;
            --i;
            splicePaste(spliceCut(i), iDestination);
            i = ii;
        }
        return true;
    }
    else{
        return false;
    }
}

//copy a whole list.
void Essay::copyList(const Essay &essay) {
    size_ = 0;
    backup_size_ = 0;
    tail_ = NULL;
    head_ = NULL;
    backup_head_ = NULL;
    backup_tail_ = NULL;
    //add non-backup
    for(iterator itr = essay.getbegin(); itr != essay.getend(); itr++){
        this->push_back(*itr);
    }

    //add backup
    for(iterator backupItr = essay.getbackup_begin(); backupItr != essay.getbackup_end(); backupItr++){
        if(backupItr.ptr_->added_ == false && backupItr.ptr_->removed_ == false){
            doubleLinkCase_push_back(backupItr);
        } else{
            this->backup_push_back(backupItr.ptr_->value_, true);
        }
    }
}

//helper for copylist. push back backup line
void Essay::backup_push_back(string str, bool removed) {
    if (backup_tail_ == NULL && backup_head_ == NULL) {
        Node* newTail_ = new Node(str);
        newTail_->removed_ = removed;
        backup_tail_ = newTail_;
        backup_head_ = newTail_;
    }
    else
    {
        Node* newTail_ = new Node(str);
        newTail_->removed_ = removed;
        backup_tail_->backup_next_ = newTail_;
        newTail_->backup_prev_ = backup_tail_;
        backup_tail_ = newTail_;
    }
    backup_size_++;
}

//helper for copylist. link the double linked node.
void Essay::doubleLinkCase_push_back(Essay::iterator i) {
    int counter = 0;
    i.backup_ = false;
    for (i; i != iterator(NULL); --i) {
        counter++;
    }
    counter--;
    iterator itr = this->begin();
    for (int ii = 0; ii < counter; ++ii) {
        itr++;
    }
    if (this->backup_tail_ != NULL && this->backup_head_ != NULL) {
    this->backup_tail_->backup_next_ = itr.ptr_;
    itr.ptr_->backup_prev_ = this->backup_tail_;
    this->backup_tail_ = itr.ptr_;
    } else{
        this->backup_head_ = itr.ptr_;
        this->backup_tail_ = itr.ptr_;
    }
    backup_size_++;
}

//destroy a list.
void Essay::destroyList() {
    if (size_ != 0) {

        for (iterator i = backup_begin(); i != backup_end();i++)
        {
            if (i.ptr_->removed_ == true) {
                i.ptr_->next_ = NULL;
                i.ptr_->prev_ = tail_;
                tail_->next_ = i.ptr_;
                tail_ = i.ptr_;
            }
        }
        for (iterator i = begin(); i != end();)
        {
            Node* n = i.ptr_->next_;
            delete i.ptr_;
            i = n;
        }
    }
}