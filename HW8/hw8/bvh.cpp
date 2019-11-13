//
// Created by huc3 on 11/5/2019.
//

#include "bvh.h"


using namespace std;
template <class T>
typename BVH<T>::iterator BVH<T>::begin() {
    return iterator();
}

template <class T>
typename BVH<T>::iterator BVH<T>::begin() const {

    return iterator();
}

template <class T>
typename BVH<T>::iterator BVH<T>::end() {
    return iterator();
}

template <class T>
typename BVH<T>::iterator BVH<T>::end() const {
    return iterator();
}

template <class T>
void BVH<T>::construct(vector<T> e) {

}

template <class T>
typename BVH<T>::iterator BVH<T>::insert(const T &leafNode) {
    return iterator();
}

template <class T>
void BVH<T>::statistics(bool printTree) {

}

template <class T>
void BVH<T>::render_recolor(ostream &o) {

}