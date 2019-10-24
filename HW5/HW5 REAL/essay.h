#ifndef __essay_h_
#define __essay_h_
#include <string>
#include "essay_iterator.h"

class Essay
{
public:
	Essay(): head_(NULL), tail_(NULL), backup_head_(NULL), backup_tail_(NULL), size_(0), backup_size_(0) {};
	Essay(const Essay& essay){copyList(essay);};
	~Essay() {destroyList();};
	typedef essayIterator iterator;

    //get the size of list
	int size();

	void operator=(const Essay& essay){
	    this->destroyList();
	    this->copyList(essay);
	}
	void debug() const;
	//push element to the head. set added to true
	void push_front(string str);
    //push back and set added to true
	void push_back(string str);
    //delete from front
	void pop_front();
    //delete from back
	void pop_back();
    //get Begin
	iterator begin();
    //get end
	iterator end();
    //get back begin, set backup_ to true
	iterator backup_begin();
    //get back up end, set backup_ to true
	iterator backup_end();
    //get Begin
    iterator getbegin() const;
    //get end
    iterator getend() const;
    //get back begin, set backup_ to true
    iterator getbackup_begin() const;
    //get back up end, set backup_ to true
    iterator getbackup_end() const;
    //insert to iterator's left
	iterator insert(iterator i, string s);
    //erase and set the non backup properties to null;
	iterator erase(iterator i);
    //revert it to backup version. added and removed must be false
	void revert();
    //number of nodes removed
	int num_removed();
    //number of nodes added
	int num_added();
    //backup stuff
	void backup();

    //helper function to splice. cut the nodes
    iterator spliceCut(iterator i);
    //helper funciton to splice, paste the nodes
    iterator splicePaste(iterator content, iterator i);
    //cut and paste, no node and or deleted
	bool splice(iterator iBegin, iterator iEnd, iterator iDestination);


private:
    //destroy a list.
    void destroyList();
    //copy a whole list.
    void copyList(const Essay &essay);
    //helper for copylist. push back backup line
    void backup_push_back(string str, bool removed);
    //helper for copylist. link the double linked node.
    void doubleLinkCase_push_back(iterator i);
	Node* tail_;
	Node* head_;
	Node* backup_head_;
	Node* backup_tail_;
	int size_;
	int backup_size_;
};


#endif