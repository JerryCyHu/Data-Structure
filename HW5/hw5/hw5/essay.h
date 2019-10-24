#pragma once
#include <string>
#include "essay_iterator.h"

class Essay
{
public:
	Essay(): head_(NULL), tail_(NULL), backup_head_(NULL), backup_tail_(NULL), size_(0), backup_size_(0) {};
	~Essay() {
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
	};
	typedef essayIterator iterator;


	int size();

	void debug() const;
	void push_front(string str);
	void push_back(string str);
	void pop_front();
	void pop_back();
	iterator begin();
	iterator end();
	iterator backup_begin();
	iterator backup_end();
	iterator insert(iterator i, string s);
	iterator erase(iterator i);
	void revert();
	int num_removed();
	int num_added();
	void backup();
	bool splice(iterator iBegin, iterator iEnd, iterator iDestination);


private:
	Node* tail_;
	Node* head_;
	Node* backup_head_;
	Node* backup_tail_;
	int size_;
	int backup_size_;
};