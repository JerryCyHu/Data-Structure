//
// Created by huc3 on 11/5/2019.
//

#ifndef HW8_BVHITERATOR_H
#define HW8_BVHITERATOR_H

#include "treeNode.h"

template <class T>
class BVHIterator{
public:
    BVHIterator(Node<T>*p = NULL, int index = 0) : ptr(p), index(index){};

    template <class K> friend class BVH;
    /////func/////
    T& operator*(){//return the shape, not the node
        return ptr->data[index];
    }
    bool operator!=(const BVHIterator& i) const{
        return ptr != i.ptr||index != i.index;
    }
    BVHIterator& operator++(){//++i
        if (index < ptr->data.size()-1){
            index++;
        }else {
            plusOperatorHelper(ptr->index);
            index = 0;
        }
        return *this;
    }
    BVHIterator operator++(int){//i++
        BVHIterator temp(*this);
        if (index < ptr->data.size()-1){
            index++;
        }else {
            plusOperatorHelper(ptr->index);
            index = 0;
        }
        return temp;
    }
    BVHIterator& operator--(){//--i
        if (index > 0){
            index--;
        }else {
            minusOperatorHelper(ptr->index);
            index = ptr->data.size()-1;
        }
        return *this;
    }
    BVHIterator operator--(int){//i--
        BVHIterator temp(*this);
        if (index > 0){
            index--;
        }else {
            minusOperatorHelper(ptr->index);
            index = ptr->data.size()-1;
        }
        return temp;
    }

private:
    Node<T>*ptr;
    int index;//shape index inside the data
    void plusOperatorHelper(int i){
        if (ptr->depth != 0) {//hasn't iterate to the root, which means not the last one
            if (ptr->index != 2) {//not the third child. No need to move to the next parent node.
                if (ptr->children[0] != NULL) {//move from the third
                    ptr = ptr->parent->children[i + 1];
                    while (ptr->children[0] != NULL) {
                        ptr = ptr->children[0];
                    }
                } else {//the leaf node
                    ptr = ptr->parent->children[i + 1];
                }
            } else {//third
                ptr = ptr->parent;
                plusOperatorHelper(ptr->index);
            }
        } else{//increment from the last one
            ptr = NULL;
        }
    }

    //basically opposite with the plushelper.
    void minusOperatorHelper(int i){
        if (ptr->depth != 0) {
            if (ptr->index != 0) {
                if (ptr->children[0] != NULL) {//move from the third
                    ptr = ptr->parent->children[i - 1];
                    while (ptr->children[0] != NULL) {
                        ptr = ptr->children[2];
                    }
                } else {
                    ptr = ptr->parent->children[i - 1];
                }
            } else {
                ptr = ptr->parent;
                minusOperatorHelper(ptr->index);
            }
        } else{
            ptr = NULL;
        }
    }
};
#endif //HW8_BVHITERATOR_H
