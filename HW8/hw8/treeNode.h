//
// Created by huc3 on 11/5/2019.
//

#ifndef HW8_TREENODE_H
#define HW8_TREENODE_H

#include <cstddef>
#include "utils.h"
#include <vector>
#include <cmath>
using namespace std;
template <class T>
class Node{
public:
    Node(vector<T> d, BoundingBox b, int depth, Node<T>*p, int i):data(d), bbox(b), depth(depth), parent(p),index(i){
        children[0] = NULL;
        children[1] = NULL;
        children[2] = NULL;
    };
    Node<T>*parent;
    Node<T>*children[3];
    vector<T> data;
    int depth;//what depth is the node at.
    int index;//which child this node is for its parent node. It can be 0,1,2
    BoundingBox bbox;
};

#endif //HW8_TREENODE_H
