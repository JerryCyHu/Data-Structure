//
// Created by huc3 on 11/5/2019.
//

#ifndef HW8_BVH_H
#define HW8_BVH_H
#include "BVHIterator.h"
#include <vector>
#include <fstream>
#include "treeNode.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "shapes.h"

template <class T>
bool intersect2(const std::vector<T> &all, const T &one) {//function that used to detect intersection.
    for (unsigned int i = 0; i < all.size(); i++) {
        if (intersect(all[i],one)) return true;
    }
    return false;
}

using namespace std;
template <class T>
class BVH {
public:
    typedef BVHIterator<T> iterator;
    BVH():root(NULL), splitThresHold(2), depthLimit(20), constructed(false), realDepth(0){};
    BVH(int s, int depthLimit):depthLimit(depthLimit), root(NULL),constructed(false), realDepth(0){
        if (s<2){
            splitThresHold = 2;
        } else{
            splitThresHold = s;
        }
    };
    //copy constructor
    BVH(const BVH<T>& obj){
        splitThresHold = obj.splitThresHold;
        depthLimit = obj.depthLimit;
        root = NULL;
        constructed = true;
        realDepth = obj.realDepth;
        construct(obj.shapeVector);
    };
    ~BVH(){
        destruct(root);
    }
    ////func///
    //iterator:
    iterator begin();
    iterator begin() const;
    iterator end();
    iterator end() const;
    //
    void construct(vector<T> e);
    bool collision(const T&shape);
    void insert(const T&shape);
    void statistics(bool print_tree) const;
    void render_recolor(std::ostream &ostr) { render_recolor(ostr,root,Color(128,128,128)); }
    //assignment operator
    void operator=(const BVH& obj){
        destruct(root);
        splitThresHold = obj.splitThresHold;
        depthLimit = obj.depthLimit;
        root = NULL;
        construct(obj.shapeVector);
    };
private:
    //boolean to see if current BVH has been constructed
    bool constructed;

    Node<T>*root;
    int splitThresHold;
    int depthLimit;

    //vector that stores all the shape. It is used in insert.
    vector<T> shapeVector;
    void statistics(bool print_tree, Node<T>* n, const std::string &indent,
                    int &node_count, int &max_depth,
                    double &inner_node_area, double &leaf_node_area) const;
    void render_recolor(std::ostream &ostr, Node<T> *n, const Color &color);

    //helper for construct
    void constructHelper(Node<T>*&n, vector<T>&e, int depth, int i);//index meaning which array index should the node be placed.

    void destruct(Node<T>* p){
            if (!p) return;
            destruct(p->children[0]);
            destruct(p->children[1]);
            destruct(p->children[2]);
            delete p;
    }

    //store the real max depth of the current BVH
    int realDepth;

    //helper func for insert
    void insertHelper(const T&shape, Node<T>*&tree);
};
///////////insert///////////////
template <class T>
void BVH<T>::insert(const T &shape) {
    shapeVector.push_back(shape);
    if (constructed == false){//not be constructed before, directly add shape into BVH
        constructed = true;
        vector<T> v;
        BoundingBox b = shape.getBox();
        root = new Node<T>(v,b, 0, NULL, 0);
        root->data.push_back(shape);
    }else {//constructed before. Call insert helper
        if (shapeVector.size() < (splitThresHold + 1) * (pow(3, realDepth))) {//no need to change depth
            insertHelper(shape, root);
        } else {//need to change depth
            destruct(root);
            construct(shapeVector);
        }
    }

}
template <class T>
void BVH<T>::insertHelper(const T &shape, Node<T>* &tree) {
    if (tree->children[0] == NULL){
        tree->bbox.extend(shape.getBox());
        tree->data.push_back(shape);
    }else {
        //first see if the shape is inside any BVH. If not, check which BVH is near the shape.
        BoundingBox b1 = tree->children[0]->bbox;
        BoundingBox b2 = tree->children[1]->bbox;
        BoundingBox b3 = tree->children[2]->bbox;
        if(b1.getMin().x<=shape.getCenter().x&&b1.getMin().y<=shape.getCenter().y&&b1.getMax().x>=shape.getCenter().x&&b1.getMax().y>=shape.getCenter().y){
            tree->bbox.extend(shape.getBox());
            insertHelper(shape, tree->children[0]);
        }else if(b2.getMin().x<=shape.getCenter().x&&b2.getMin().y<=shape.getCenter().y&&b2.getMax().x>=shape.getCenter().x&&b2.getMax().y>=shape.getCenter().y){
            tree->bbox.extend(shape.getBox());
            insertHelper(shape, tree->children[1]);
        }else if(b3.getMin().x<=shape.getCenter().x&&b3.getMin().y<=shape.getCenter().y&&b3.getMax().x>=shape.getCenter().x&&b3.getMax().y>=shape.getCenter().y){
            tree->bbox.extend(shape.getBox());
            insertHelper(shape, tree->children[2]);
        }else {
            int distance1 = distance(shape.getCenter(),
                                     Point((tree->children[0]->bbox.getMax().x - tree->children[0]->bbox.getMin().x) /
                                           2,
                                           (tree->children[0]->bbox.getMax().y - tree->children[0]->bbox.getMin().y) /
                                           2));
            int distance2 = distance(shape.getCenter(),
                                     Point((tree->children[1]->bbox.getMax().x - tree->children[1]->bbox.getMin().x) /
                                           2,
                                           (tree->children[1]->bbox.getMax().y - tree->children[1]->bbox.getMin().y) /
                                           2));
            int distance3 = distance(shape.getCenter(),
                                     Point((tree->children[2]->bbox.getMax().x - tree->children[2]->bbox.getMin().x) /
                                           2,
                                           (tree->children[2]->bbox.getMax().y - tree->children[2]->bbox.getMin().y) /
                                           2));
            if (distance3 < distance2 && distance3 < distance1) {
                tree->bbox.extend(shape.getBox());
                insertHelper(shape, tree->children[2]);
            } else if (distance2 < distance3 && distance2 < distance1) {
                tree->bbox.extend(shape.getBox());
                insertHelper(shape, tree->children[1]);
            } else {
                tree->bbox.extend(shape.getBox());
                insertHelper(shape, tree->children[0]);
            }
        }
    }
}

//////////////////
template <class T>
typename BVH<T>::iterator BVH<T>::begin() {
    if (!root){
        return NULL;
    } else {
        Node<T> *n = root;
        while (n->children[0] != NULL) {
            n = n->children[0];
        }
        iterator itr = iterator(n, 0);
        return itr;
    }
}

template <class T>
typename BVH<T>::iterator BVH<T>::begin() const {
    if (!root){
        return NULL;
    } else {
        Node<T> *n = root;
        while (n->children[0] != NULL) {
            n = n->children[0];
        }

        iterator itr = iterator(n, 0);
        return itr;
    }
}

template <class T>
typename BVH<T>::iterator BVH<T>::end() {
    return NULL;
}

template <class T>
typename BVH<T>::iterator BVH<T>::end() const {
    return NULL;
}
/////all for construct
template <class T>
bool sortingWithX(const T& l, const T& r){//sort with respect to x
    return l.getCenter().x<=r.getCenter().x;
}
template <class T>
bool sortingWithY(const T& l, const T& r){
    return l.getCenter().y<=r.getCenter().y;
}
template <class T>
void BVH<T>::construct(vector<T> e) {
    realDepth = 0;
    constructed = true;
    shapeVector = e;
    BoundingBox b = e[0].getBox();
    for (int i = 1; i < e.size(); ++i) {
        b.extend(e[i].getBox());
    }
    if (e.size()!=1) {
        if (b.getMax().x - b.getMin().x > b.getMax().y - b.getMin().y) {//sort with respect to x
            sort(e.begin(), e.end(), sortingWithX<T>);
        } else {
            sort(e.begin(), e.end(), sortingWithY<T>);
        }
    }
    vector<T> emptyV;
    Node<T>* a = new Node<T>(emptyV,b,0, NULL, 0);
    root = a;
    vector<T> v1;
    vector<T> v2;
    vector<T> v3;
    if(e.size()>splitThresHold&&depthLimit>0){
        int counter1, counter2, counter3;
        if(e.size()%3 == 1){
            counter1 = e.size()/3;
            counter2 = e.size()/3*2;
            counter3 = e.size()-1;
        } else if(e.size()%3 == 2){
            counter1 = e.size()/3;
            counter2 = e.size()/3*2+1;
            counter3 = e.size()-1;
        } else{
            counter1 = e.size()/3-1;
            counter2 = e.size()/3*2-1;
            counter3 = e.size()-1;
        }
        for (int i = 0; i <= counter1 ; ++i) {
            v1.push_back(e[i]);
        }
        for(int i = counter1+1; i <= counter2; ++i){
            v2.push_back(e[i]);
        }
        for (int i = counter2+1; i <= counter3; ++i) {
            v3.push_back(e[i]);
        }
        constructHelper(root, v1, 1, 0);
        constructHelper(root, v2, 1, 1);
        constructHelper(root, v3, 1, 2);
    } else{
        delete a;
        Node<T>* a = new Node<T>(e,b,0,NULL, 0);
        root = a;
    }
}
template <class T>
void BVH<T>::constructHelper(Node<T>*&n, vector<T>&e, int depth, int i) {
    if  (realDepth<depth){
        realDepth = depth;
    }
    BoundingBox b = e[0].getBox();
    for (int i = 1; i < e.size(); ++i) {
        b.extend(e[i].getBox());
    }
    if(b.getMax().x-b.getMin().x > b.getMax().y-b.getMin().y){//sort with respect to x
        sort(e.begin(),e.end(),sortingWithX<T>);
    } else{
        sort(e.begin(),e.end(),sortingWithY<T>);
    }
    vector<T> emptyV;
    Node<T>* a = new Node<T>(emptyV,b,depth,n, i);
    n->children[i] = a;
    ////data all set, prepare for recursion
    if(e.size()>splitThresHold&&depthLimit>depth){
        vector<T> v1;
        vector<T> v2;
        vector<T> v3;
        int counter1, counter2, counter3;
        if(e.size()%3 == 1){
            counter1 = e.size()/3;
            counter2 = e.size()/3*2;
            counter3 = e.size()-1;
        } else if(e.size()%3 == 2){
            counter1 = e.size()/3;
            counter2 = e.size()/3*2+1;
            counter3 = e.size()-1;
        } else{
            counter1 = e.size()/3-1;
            counter2 = e.size()/3*2-1;
            counter3 = e.size()-1;
        }
        for (int i = 0; i <= counter1 ; ++i) {
            v1.push_back(e[i]);
        }
        for(int i = counter1+1; i <= counter2; ++i){
            v2.push_back(e[i]);
        }
        for (int i = counter2+1; i <= counter3; ++i) {
            v3.push_back(e[i]);
        }
        constructHelper(n->children[i], v1, depth+1, 0);
        constructHelper(n->children[i], v2, depth+1, 1);
        constructHelper(n->children[i], v3, depth+1, 2);
    } else{
        delete a;
        Node<T>* a = new Node<T>(e,b,depth,n, i);
        n->children[i] = a;
    }
}

template <class T>
bool BVH<T>::collision(const T &shape) {
        if (intersect2<T>(shapeVector,shape)){//collides
            return true;
        }
    return false;
}

template <class T>
void BVH<T>::statistics(bool print_tree) const {

    // node count & maximum depth can be used to partially evaluate if
    // the tree is mostly well-balanced.
    int node_count = 0;
    int max_depth = 0;

    //
    // Bittner, Hapala, & Havran, "Incremental BVH construction for ray
    // tracing". Computers & Graphics 2014.
    //
    // summarize the "surface area heuristic" for predicting the
    // efficiency of a bounding volume hierarchy.
    //
    // We calculate the sum of the (surface) area of all inner
    // (non-leaf) nodes and divide by the area of the entire scene.  It
    // is generally better for the inner nodes to have small surface
    // area -- which indicates the hierarchy is small and efficient, and
    // we can quickly navigate to the relevant leaf nodes.
    //
    double inner_node_area = 0;

    // We also calculate the sum of the leaf node surface area (again
    // divided by the scene area).  The leaf node area is multiplied
    // (penalized) by the number of elements at that leaf node.  We hope
    // this number is also small.
    //
    double leaf_node_area = 0;


    // sweep over the tree and print the results
    statistics(print_tree,root,"",node_count, max_depth, inner_node_area, leaf_node_area);
    std::cout << "node count:      " << std::setw(7) << node_count << std::endl;
    std::cout << "max depth:       " << std::setw(7) << max_depth << std::endl;
    std::cout << "inner node area: " << std::fixed << std::setw(7) << std::setprecision(3) << inner_node_area << std::endl;
    std::cout << "leaf node area:  " << std::fixed << std::setw(7) << std::setprecision(3) << leaf_node_area << std::endl;
}


// The core recursive function to collect the statistics above.  If
// the print_tree bool is enabled, we will also print data about the
// tree for debugging and autograding.
template <class T>
void BVH<T>::statistics(bool print_tree,
                        Node<T>* n,
                        const std::string &indent,
                        int &node_count,
                        int &max_depth,
                        double &inner_node_area,
                        double &leaf_node_area) const {

    node_count++;
    max_depth = std::max(n->depth,max_depth);
    // scale the area by the area of the scene
    double area = n->bbox.getArea() / double(1000*1000);
    if (n->data.size() != 0) {
        leaf_node_area += n->data.size() * area;
        if (print_tree) {
            std::cout << indent + "leaf area=" << std::setprecision(3) << area << " " << n->bbox << " elements:";
            for (unsigned int i = 0; i < n->data.size(); i++) {
                std::cout << " " << n->data[i].getBox();
            }
            std::cout << std::endl;
        }
    } else {
        inner_node_area += area;
        if (print_tree) {
            std::cout << indent + "inner area=" << std::setprecision(3) << area << " " << n->bbox << std::endl;
        }
        statistics(print_tree,n->children[0],indent+"   ",node_count,max_depth,inner_node_area,leaf_node_area);
        statistics(print_tree,n->children[1],indent+"   ",node_count,max_depth,inner_node_area,leaf_node_area);
        statistics(print_tree,n->children[2],indent+"   ",node_count,max_depth,inner_node_area,leaf_node_area);
    }
}

// =============================================================================
// helper functions for rendering


template <class T>
void BVH<T>::render_recolor(std::ostream &ostr, Node<T> *n, const Color &color) {

    // draw the bounding box of this node as a transparent colored rectangle
    n->bbox.render(ostr,color);

    if (n->children[0] != NULL) {

        // prepare variations of this node color for the 3 children
        Color red(255,0,0);
        Color green(0,255,0);
        Color blue(0,0,255);
        // blend the colors
        if (color.r != 128 && color.g != 128 && color.b != 128) {
            float m = 0.33;
            red.mix(color,m);
            green.mix(color,m);
            blue.mix(color,m);
        }

        // recurse to the children
        render_recolor(ostr,n->children[0],red);
        render_recolor(ostr,n->children[1],green);
        render_recolor(ostr,n->children[2],blue);

    } else {

        // if this is a leaf node, modify the color of all elements to
        // match the transparent box color.
        for (unsigned int i = 0; i < n->data.size(); i++) {
            n->data[i].setColor(color);
        }
    }
}
#endif //HW8_BVH_H
