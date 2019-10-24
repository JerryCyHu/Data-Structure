#ifndef __essay_iterator_h_
#define __essay_iterator_h_
#include"node.h"

class essayIterator {
public:
	// default constructor, copy constructor, assignment operator, & destructor
	essayIterator(Node* p = NULL,bool b = false) : ptr_(p),backup_(b) {}

	// dereferencing operator gives access to the value at the pointer
	string& operator*() { return ptr_->value_; }

	// increment & decrement operators
	// pre-increment, e.g., ++iter
	essayIterator& operator++() {
		if (!backup_)
		{
			ptr_ = ptr_->next_;
			return *this;
		}
		else
		{
			ptr_ = ptr_->backup_next_;
			return *this;
		}
	}
	// post-increment, e.g., iter++
	essayIterator operator++(int) {
		essayIterator temp(*this);
		if (!backup_)
			ptr_ = ptr_->next_;
		else
			ptr_ = ptr_->backup_next_;
		return temp;
	}
	// pre-decrement, e.g., --iter
	essayIterator& operator--() {
		if (!backup_)
			ptr_ = ptr_->prev_;
		else
			ptr_ = ptr_->backup_prev_;
		return *this;
	}
	// post-decrement, e.g., iter--
	essayIterator operator--(int) {
		essayIterator temp(*this);
		if (!backup_)
			ptr_ = ptr_->prev_;
		else
			ptr_ = ptr_->backup_prev_;
		return temp;
	}
	// the essay class needs access to the private ptr_ member variable
	friend class Essay;

	// Comparions operators are straightforward
	bool operator==(const essayIterator& r) const {
		return ptr_ == r.ptr_;
	}
	bool operator!=(const essayIterator& r) const {
		return ptr_ != r.ptr_;
	}

private:
	// REPRESENTATION
	Node* ptr_;    // ptr to node in the list
	bool backup_; //whether in backup mode
};

#endif