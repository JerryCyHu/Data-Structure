#include <iostream>
class Node {
public:
    int value;
    Node* left;
    Node* right;
};

bool shape_match(Node* a, Node* b){
    if(a==NULL&&b==NULL){
        return true;
    }
    if((a == NULL&&b!=NULL)||(a!=NULL&&b==NULL)){
        return false;
    }
    return shape_match(a->left,b->left)&&shape_match(a->right,b->right);
}

Node* find_subtree_match(Node* t, Node* p){
    if (t==NULL)
        return NULL;
    if (shape_match(t,p)){
        return t;
    }else{
        Node* l = find_subtree_match(t->left, p);
        Node* r = find_subtree_match(t->right, p);
        if(l){
            return l;
        }else if(r){
            return r;
        }else{
            return NULL;
        }
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    Node* a = new Node();
    a->left = new Node();
    a->right = new Node();
    a->right->right = new Node();
    a->left->left = new Node();
    a->left->right = new Node();
    a->value = 5;
    a->left->value = 7;
    a->left->left->value = 6;
    a->left->right->value = 11;
    a->right->value = 13;
    a->right->right->value = 21;

    Node* b = new Node();
    b->left = new Node();
    b->right = new Node();
    b->right->right = new Node();
    b->left->left = new Node();
    b->left->right = new Node();
    b->value = 5;
    b->left->value = 7;
    b->left->left->value = 6;
    b->left->right->value = 11;
    b->right->value = 13;
    b->right->right->value = 21;

    Node* c = new Node();
    c->right = a;
    c->left = new Node();
    c->left->left = new Node();
    c->left->right = new Node();
    c->value = 15;
    c->left->value = 20;
    c->left->left->value = 4;
    c->left->right->value = 12;
    if (shape_match(a,b)){
        std::cout<<"fuck";
    }
    std::cout<<(find_subtree_match(c,a))->value;

    return 0;
}
