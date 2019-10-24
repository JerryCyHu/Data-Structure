//
// Created by huc3 on 10/20/2019.
//

#ifndef HW6_NODE_H
#define HW6_NODE_H

#include <string>
#include <vector>
using namespace std;


class Node {
public:
    Node(char n, int x1, int y1)
    : name(n), startX(x1), startY(y1), endX(0), endY(0), onBridge(false){};
    char name;
    int startY;
    int startX;
    int endY;
    int endX;
    vector<vector<Node>> paths;
    bool onBridge;
};


#endif //HW6_NODE_H
