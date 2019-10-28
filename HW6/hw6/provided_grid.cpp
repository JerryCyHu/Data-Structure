#include "provided_grid.h"
#include <cassert>

using namespace std;
// =============================================================================

// constructor loads the input puzzle board
Grid::Grid(const std::string &filename) {
  std::ifstream istr(filename);
  assert (istr.good());
  
  std::string s;
  while (istr >> s) { endpoints.push_back(s); }

  // initially all of the vertical and horizontal edges are blank!
  //
  // NOTE note that the dimensions are off by one of the endpoints.
  // We have 1 fewer row of vertical path edges and 1 fewer column of
  // horizontal path edges.
  verticals = std::vector<std::string>(height()-1,std::string(width(),' '));
  horizontals = std::vector<std::string>(height(),std::string(width()-1,' '));

  //Put every Node into the nodeVector.
  // The point such as A, B, # are nodes.
    for (int i = 0; i<endpoints.size(); ++i) {//i is y
        for (int j = 0; j < endpoints[i].length() ; ++j) {//j is x
            bool exist = false;
            Node* b;//Temporary node for modifying node inside nodeVector.
            for (Node& a : nodeVector) {
                if (endpoints[i][j] == a.name&&a.name!='#') {
                    exist = true;
                    b = &a;
                    break;
                }
            }
            if (!exist){
                if (endpoints[i][j]!='.'){
                    Node n(endpoints[i][j], j, i);
                    nodeVector.push_back(n);
                }
            } else{
                b->endX = j;
                b->endY = i;
            }
        }
    }
}

// =============================================================================

void Grid::print() {

  // loop over the rows of the grid
  for (int j = 0; j < height(); j++) {

    // first print the horizontal cell boundaries
    for (int i = 0; i < width(); i++) {
      char bar = (j==0) ? '-' : ' ';
      char vertical = (j != 0) ? verticals[j-1][i] : bar;
      std::cout << "+" << bar << vertical << bar;
    }
    std::cout << "+" << std::endl;
    
    // then print 3 rows for the middle of each cell
    for (int k = 0; k < 3; k++) {

      for (int i = 0; i < width(); i++) {
        
        // what symbol should be printed in the center of this cell?
        char center = print_center(i,j);

        // what horizontal path edges run through this cell?
        char horizontal_left = (k == 1 && i != 0) ? horizontals[j][i-1] : ' ';
        char horizontal_right = (k == 1 && i+1 < width()) ? horizontals[j][i] : ' ';
        // the left edge of the cell
        char side = (i==0) ? '|' : horizontal_left;

        // do the printing
        if (k == 0) center = (j != 0) ? verticals[j-1][i] : ' ';
        if (k == 2) center = (j+1 < height()) ? verticals[j][i] : ' ';
        std::cout << side << horizontal_left << center << horizontal_right;
      }

      // the right edge of the whole grid
      std::cout << "|" << std::endl;
    }
  }

  // the lower edge of the whole grid
  for (int i = 0; i < width(); i++) {
    std::cout << "+" << std::string(3,'-');
  }
  std::cout << "+" << std::endl;
}

char Grid::print_center(int i, int j) {
  assert (i >= 0 && i < width());
  assert (j >= 0 && j < height());

  if (endpoints[j][i] != '.') { return endpoints[j][i]; }
  
  // if this is not an endpoint or bridge cell, look at the 4 edges
  // if any of them is a path, take that color for the center
  
  char up    = (j == 0)          ? ' ' : verticals  [j-1][i  ];
  char down  = (j == height()-1) ? ' ' : verticals  [j  ][i  ];
  char left  = (i == 0)          ? ' ' : horizontals[j  ][i-1];
  char right = (i == width()-1)  ? ' ' : horizontals[j  ][i  ];

  char center = up;
  if (center == ' ') center = down;
  if (center == ' ') center = right;
  if (center == ' ') center = left;
  return center;
}

void Grid::oneColorHelperUp(vector<Node>& p, Node& node) {
    node.startY--;

    bool onlyGoStraight = false;//crossing a bridge.
    if(node.startY < 0) {
        p.push_back(node);
        return;
    }
    if (node.startX < 0) {
        p.push_back(node);
        return;
    }
    if (node.startX > width()-1) {
        p.push_back(node);
        return;
    }
    for (Node& n : p){//if cross itself
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
    }
    for (Node& n : nodeVector){
        if(n.name != '#') {
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
            if (node.startX == n.endX && node.startY == n.endY && node.name != n.name) {
                p.push_back(node);
                return;
            }
        }
        if(n.name == '#'){//bridge
            if (node.startX == n.startX&&node.startY == n.startY){
                onlyGoStraight = true;
                node.onBridge = true;
                break;
            }
        }
    }

    if (node.startX == node.endX && node.startY == node.endY){//got to the destination
        for (int i = 0; i < nodeVector.size(); ++i) {
            if (nodeVector[i].name == node.name){
                nodeVector[i].paths.push_back(p);
                break;
            }
        }
        p.push_back(node);
        return;
    }

    p.push_back(node);
    node.onBridge = false;

    if (onlyGoStraight){
        oneColorHelperUp(p,node);
        node.startY++;
        p.pop_back();
    } else{
        oneColorHelperUp(p,node);
        node.startY++;
        p.pop_back();
        oneColorHelperLeft(p,node);
        node.startX++;
        p.pop_back();
        oneColorHelperRight(p,node);
        node.startX--;
        p.pop_back();
    }

}
void Grid::oneColorHelperDown(vector<Node>& p, Node& node) {
    node.startY++;

    bool onlyGoStraight = false;//crossing a bridge.
    if(node.startY > height()-1) {
        p.push_back(node);
        return;
    }
    if (node.startX < 0) {
        p.push_back(node);
        return;
    }
    if (node.startX > width()-1) {
        p.push_back(node);
        return;
    }
    for (Node& n : p){
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
    }
    for (Node& n : nodeVector){
        if(n.name != '#') {
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
            if (node.startX == n.endX && node.startY == n.endY && node.name != n.name) {
                p.push_back(node);
                return;
            }
        }
        if(n.name == '#'){//bridge
            if (node.startX == n.startX&&node.startY == n.startY){
                onlyGoStraight = true;
                node.onBridge = true;
                break;
            }
        }
    }

    if (node.startX == node.endX && node.startY == node.endY){//got to the destination
        for (int i = 0; i < nodeVector.size(); ++i) {
            if (nodeVector[i].name == node.name){
                nodeVector[i].paths.push_back(p);
                break;
            }
        }
        p.push_back(node);
        return;
    }

    p.push_back(node);
    node.onBridge = false;

    if (onlyGoStraight){
        oneColorHelperDown(p,node);
        node.startY--;
        p.pop_back();
    } else{
        oneColorHelperDown(p,node);
        node.startY--;
        p.pop_back();
        oneColorHelperLeft(p,node);
        node.startX++;
        p.pop_back();
        oneColorHelperRight(p,node);
        node.startX--;
        p.pop_back();
    }
}
void Grid::oneColorHelperLeft(vector<Node>& p, Node& node) {

    node.startX--;

    bool onlyGoStraight = false;//crossing a bridge.
    if(node.startX < 0) {
        p.push_back(node);
        return;
    }
    if (node.startY < 0) {
        p.push_back(node);
        return;
    }
    if (node.startY > height()-1) {
        p.push_back(node);
        return;
    }
    for (Node& n : p){
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
    }
    for (Node& n : nodeVector){
        if (n.name != '#') {
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
            if (node.startX == n.endX && node.startY == n.endY && node.name != n.name) {
                p.push_back(node);
                return;
            }
        }
        if(n.name == '#'){//bridge
            if (node.startX == n.startX&&node.startY == n.startY){
                onlyGoStraight = true;
                node.onBridge = true;
                break;
            }
        }
    }
    if (node.startX == node.endX && node.startY == node.endY){//got to the destination
        for (int i = 0; i < nodeVector.size(); ++i) {
            if (nodeVector[i].name == node.name){
                nodeVector[i].paths.push_back(p);
                break;
            }
        }
        p.push_back(node);
        return;
    }

    p.push_back(node);
    node.onBridge = false;

    if (onlyGoStraight){
        oneColorHelperLeft(p,node);
        node.startX++;
        p.pop_back();
    } else{
        oneColorHelperUp(p,node);
        node.startY++;
        p.pop_back();
        oneColorHelperDown(p,node);
        node.startY--;
        p.pop_back();
        oneColorHelperLeft(p,node);
        node.startX++;
        p.pop_back();
    }
}
void Grid::oneColorHelperRight(vector<Node>& p, Node& node) {
    node.startX++;

    bool onlyGoStraight = false;//crossing a bridge.
    if(node.startX > width()-1) {
        p.push_back(node);
        return;
    }
    if (node.startY < 0) {
        p.push_back(node);
        return;
    }
    if (node.startY > height()-1) {
        p.push_back(node);
        return;
    }
    for (Node& n : p){
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
    }
    for (Node& n : nodeVector){
        if(n.name != '#') {
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
            if (node.startX == n.endX && node.startY == n.endY && node.name != n.name) {
                p.push_back(node);
                return;
            }
        }
        if(n.name == '#'){//bridge
            if (node.startX == n.startX&&node.startY == n.startY){
                onlyGoStraight = true;
                node.onBridge = true;
                break;
            }
        }
    }

    if (node.startX == node.endX && node.startY == node.endY){//got to the destination
        for (int i = 0; i < nodeVector.size(); ++i) {
            if (nodeVector[i].name == node.name){
                nodeVector[i].paths.push_back(p);
                break;
            }
        }
        p.push_back(node);
        return;
    }

    p.push_back(node);
    node.onBridge = false;

    if (onlyGoStraight){
        oneColorHelperRight(p,node);
        node.startX--;
        p.pop_back();
    } else{
        oneColorHelperUp(p,node);
        node.startY++;
        p.pop_back();
        oneColorHelperDown(p,node);
        node.startY--;
        p.pop_back();
        oneColorHelperRight(p,node);
        node.startX--;
        p.pop_back();
    }
}

void Grid::one_color_solution(char name){
    bool valid = false;
    int i;
    Node*targetN;
    for (i = 0; i < nodeVector.size(); ++i) {//see if name is inside nodeVector
        if (nodeVector[i].name == name){
            valid = true;
            targetN = &nodeVector[i];
            break;
        }
    }
    if (valid){
        Node n = nodeVector[i];
        pathNodes.clear();
        oneColorHelperUp(pathNodes, n);
        n.startY++;
        pathNodes.clear();
        oneColorHelperDown(pathNodes,n);
        n.startY--;
        pathNodes.clear();
        oneColorHelperRight(pathNodes,n);
        n.startX--;
        pathNodes.clear();
        oneColorHelperLeft(pathNodes,n);
        n.startX++;
        pathNodes.clear();
        //////////////////get all paths, then editing 'targetN'.
        for (int i = 0; i < targetN->paths.size(); ++i) {
            horizontals.clear();
            verticals.clear();
            verticals = std::vector<std::string>(height()-1,std::string(width(),' '));
            horizontals = std::vector<std::string>(height(),std::string(width()-1,' '));
            vector<Node> &v = targetN->paths[i];
            vhConstructorForOCS(v, targetN);
            print();
            cout << endl;
        }
        horizontals.clear();
        verticals.clear();
        verticals = std::vector<std::string>(height()-1,std::string(width(),' '));
        horizontals = std::vector<std::string>(height(),std::string(width()-1,' '));
        int count = targetN->paths.size();
        if(count > 0){
            cout << "Found " << count << " Path(s) for Color '" << name << "'" << endl;
        }else{
            print();
            cout<<endl << "No Paths for Color '" << count << "'" << endl;
        }
    } else{
        cerr<<"Name not found.";
    }
}

// =============================================================================

// OBVIOUSLY, THIS IS NOT HOW YOU ARE SUPPOSED TO SOLVE THE ASSIGNMENT!
// this is for print function demonstration purposes only

void Grid::hardcoded_solution(const std::string &filename) {
  
  if (filename == "puzzle_1.txt") {
    horizontals[1][1] = 'b';
    horizontals[1][2] = 'b';

    horizontals[0][0] = 'a';
    horizontals[0][1] = 'a';
    horizontals[0][2] = 'a';
    horizontals[2][0] = 'a';
    horizontals[2][1] = 'a';
    horizontals[2][2] = 'a';
    verticals[0][0] = 'a';
    verticals[1][0] = 'a';
  }


  else if (filename == "puzzle_2.txt") {
    horizontals[2][0] = 'c';
    verticals[1][0] = 'c';

    horizontals[0][0] = 'a';
    horizontals[0][1] = 'a';
    horizontals[2][2] = 'a';
    verticals[0][2] = 'a';
    verticals[1][2] = 'a';
  
    horizontals[1][1] = 'b';
    horizontals[1][2] = 'b';
    verticals[0][3] = 'b';
  }

  else {
    std::cout << "ERROR: no hardcoded solution for " << filename << std::endl;
    exit(0);
  }

}

void Grid::vhConstructorForOCS(vector<Node>& p, Node* target) {
    char nodeName = target->name+32;
    for (int i = 0; i < p.size(); ++i) {
        if (i == 0){//from start
            if (target->startX == p[i].startX){//up & down
                if (target->startY > p[i].startY) {//goes up from start
                    this->verticals[p[i].startY][p[i].startX] = nodeName;
                } else if (target->startY < p[i].startY){//goes down from start
                    this->verticals[target->startY][target->startX] = nodeName;
                }
            }else if (target->startY == p[i].startY){//left & right
                if (target->startX > p[i].startX) {//goes left from start
                    this->horizontals[p[i].startY][p[i].startX] = nodeName;
                }else if (target->startX < p[i].startX) {//goes right from start
                    this->horizontals[target->startY][target->startX] = nodeName;
                }
            }
        }
        if (i == p.size()-1){//to end
            if (target->endX == p[i].startX){//up & down
                if (target->endY > p[i].startY) {//goes down to end
                    this->verticals[p[i].startY][p[i].startX] = nodeName;
                } else if (target->endY < p[i].startY){//goes up to end
                    this->verticals[target->endY][target->endX] = nodeName;
                }
            }else if (target->endY == p[i].startY){//left & right
                if (target->endX > p[i].startX) {//goes right to end
                    this->horizontals[p[i].startY][p[i].startX] = nodeName;
                }else if (target->endX < p[i].startX) {//goes left to end
                    this->horizontals[target->endY][target->endX] = nodeName;
                }
            }
        }
        if(i!=p.size()-1){//in middle
            if (p[i].startX == p[i+1].startX){//up & down
                if (p[i].startY > p[i+1].startY) {
                    this->verticals[p[i+1].startY][p[i+1].startX] = nodeName;
                } else if (p[i].startY < p[i+1].startY){
                    this->verticals[p[i].startY][p[i].startX] = nodeName;
                }
            } else if (p[i].startY == p[i+1].startY){
                if (p[i].startX > p[i+1].startX) {
                    this->horizontals[p[i+1].startY][p[i+1].startX] = nodeName;
                } else if (p[i].startX < p[i+1].startX){
                    this->horizontals[p[i].startY][p[i].startX] = nodeName;
                }
            }
        }
    }
}

void Grid::all_paths_solution(){
    getAllNodesAllPaths();
    /////////print each node's paths first//////
    for (int i = 0; i < nodeVector.size(); ++i) {
        if (nodeVector[i].name != '#') {
            cout << nodeVector[i].name << endl;
            cout << nodeVector[i].name << " " << nodeVector[i].paths.size() << endl;
        }
    }
    //////////////////get all paths, then editing 'targetN'.
    int count = 0;
    for (int i = 0; i < nodeVector.size(); ++i) {
        if (nodeVector[i].name != '#'){
            Node*targetN = &nodeVector[i];
            for (int i = 0; i < targetN->paths.size(); ++i) {
                horizontals.clear();
                verticals.clear();
                verticals = std::vector<std::string>(height()-1,std::string(width(),' '));
                horizontals = std::vector<std::string>(height(),std::string(width()-1,' '));
                vector<Node> &v = targetN->paths[i];
                vhConstructorForOCS(v, targetN);
                print();
                cout << endl;
            }
            horizontals.clear();
            verticals.clear();
            verticals = std::vector<std::string>(height()-1,std::string(width(),' '));
            horizontals = std::vector<std::string>(height(),std::string(width()-1,' '));
            count += targetN->paths.size();
        }
    }
    if(count > 0){
        cout << "Found " << count << " Path(s)" << endl;
    }else{
        print();
        cout <<endl << "Found No Paths" << endl;
    }
}

void Grid::getAllNodesAllPaths() {
    for (int i = 0; i < nodeVector.size(); ++i) {
        if (nodeVector[i].name != '#'){
            Node n = nodeVector[i];
            pathNodes.clear();
            oneColorHelperUp(pathNodes, n);
            n.startY++;
            pathNodes.clear();
            oneColorHelperDown(pathNodes,n);
            n.startY--;
            pathNodes.clear();
            oneColorHelperRight(pathNodes,n);
            n.startX--;
            pathNodes.clear();
            oneColorHelperLeft(pathNodes,n);
            n.startX++;
            pathNodes.clear();
        }
    }
}

void Grid::all_solutions() {
    getSolutionVector();//all data are setted up
    int count = solutionPackedVector.size();
    for (int i = 0; i < solutionPackedVector.size(); ++i) {
        horizontals.clear();
        verticals.clear();
        verticals = std::vector<std::string>(height()-1,std::string(width(),' '));
        horizontals = std::vector<std::string>(height(),std::string(width()-1,' '));
        for (int j = 0; j < solutionPackedVector[i].size(); ++j) {
            vhConstructorForOCS(solutionPackedVector[i][j], &targetNodes[j]);
        }
        print();
        horizontals.clear();
        verticals.clear();
        verticals = std::vector<std::string>(height()-1,std::string(width(),' '));
        horizontals = std::vector<std::string>(height(),std::string(width()-1,' '));
    }
    cout<<endl;
    if(count > 0){
        cout << "Found " << count << " Solution(s)" <<endl;
    }else{
        print();
        cout <<endl << "Found No Solutions" << endl;
    }
}

void Grid::getAllValidStrategies(vector<Node>&solutionpathVector, int indexOfNodes) {
    Node n = targetNodes[indexOfNodes];
    allSolutionHelperUp(solutionpathVector, n, indexOfNodes);
    n.startY++;
    solutionpathVector.pop_back();
    allSolutionHelperDown(solutionpathVector,n, indexOfNodes);
    n.startY--;
    solutionpathVector.pop_back();
    allSolutionHelperRight(solutionpathVector,n, indexOfNodes);
    n.startX--;
    solutionpathVector.pop_back();
    allSolutionHelperLeft(solutionpathVector,n, indexOfNodes);
    n.startX++;
    solutionpathVector.pop_back();

}

void Grid::allSolutionHelperUp(vector<Node>& p, Node& node, int nodeIndex) {
    node.startY--;

    bool onlyGoStraight = false;//crossing a bridge.
    if(node.startY < 0) {
        p.push_back(node);
        return;
    }
    if (node.startX < 0) {
        p.push_back(node);
        return;
    }
    if (node.startX > width()-1) {
        p.push_back(node);
        return;
    }
    for (Node& n : p){//if cross itself
        if (node.startX == n.startX && node.startY == n.startY) {
            if(!(node.name!=n.name&&n.onBridge == true)){
                p.push_back(node);
                return;
            }
        }
    }
    for (Node& n : nodeVector){
        if(n.name != '#') {
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
            if (node.startX == n.endX && node.startY == n.endY && node.name != n.name) {
                p.push_back(node);
                return;
            }
        }
        if(n.name == '#'){//bridge
            if (node.startX == n.startX&&node.startY == n.startY){
                onlyGoStraight = true;
                node.onBridge = true;
                break;
            }
        }
    }

    if (node.startX == node.endX && node.startY == node.endY){//got to the destination
        for (int i = 0; i < nodeVector.size(); ++i) {
            if (nodeVector[i].name == node.name){
                nodeVector[i].paths.push_back(p);
                break;
            }
        }
        if (nodeIndex==targetNodes.size()-1){//the last targetnode
            allSolutionVector.push_back(p);
        } else {
            getAllValidStrategies(p,nodeIndex+1);
        }
        p.push_back(node);
        return;
    }

    p.push_back(node);
    node.onBridge = false;

    if (onlyGoStraight){
        allSolutionHelperUp(p,node,nodeIndex);
        node.startY++;
        p.pop_back();
    } else{
        allSolutionHelperUp(p,node,nodeIndex);
        node.startY++;
        p.pop_back();
        allSolutionHelperLeft(p,node,nodeIndex);
        node.startX++;
        p.pop_back();
        allSolutionHelperRight(p,node,nodeIndex);
        node.startX--;
        p.pop_back();
    }

}
void Grid::allSolutionHelperDown(vector<Node>& p, Node& node, int nodeIndex) {
    node.startY++;

    bool onlyGoStraight = false;//crossing a bridge.
    if(node.startY > height()-1) {
        p.push_back(node);
        return;
    }
    if (node.startX < 0) {
        p.push_back(node);
        return;
    }
    if (node.startX > width()-1) {
        p.push_back(node);
        return;
    }
    for (Node& n : p){
        if (node.startX == n.startX && node.startY == n.startY) {
            if(!(node.name!=n.name&&n.onBridge == true)){
                p.push_back(node);
                return;
            }
        }
    }
    for (Node& n : nodeVector){
        if(n.name != '#') {
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
            if (node.startX == n.endX && node.startY == n.endY && node.name != n.name) {
                p.push_back(node);
                return;
            }
        }
        if(n.name == '#'){//bridge
            if (node.startX == n.startX&&node.startY == n.startY){
                onlyGoStraight = true;
                node.onBridge = true;
                break;
            }
        }
    }

    if (node.startX == node.endX && node.startY == node.endY){//got to the destination
        for (int i = 0; i < nodeVector.size(); ++i) {
            if (nodeVector[i].name == node.name){
                nodeVector[i].paths.push_back(p);
                break;
            }
        }
        if (nodeIndex==targetNodes.size()-1){//the last targetnode
            allSolutionVector.push_back(p);
        } else {
            getAllValidStrategies(p,nodeIndex+1);
        }
        p.push_back(node);
        return;
    }

    p.push_back(node);
    node.onBridge = false;

    if (onlyGoStraight){
        allSolutionHelperDown(p,node,nodeIndex);
        node.startY--;
        p.pop_back();
    } else{
        allSolutionHelperDown(p,node,nodeIndex);
        node.startY--;
        p.pop_back();
        allSolutionHelperLeft(p,node,nodeIndex);
        node.startX++;
        p.pop_back();
        allSolutionHelperRight(p,node,nodeIndex);
        node.startX--;
        p.pop_back();
    }
}
void Grid::allSolutionHelperLeft(vector<Node>& p, Node& node, int nodeIndex) {

    node.startX--;

    bool onlyGoStraight = false;//crossing a bridge.
    if(node.startX < 0) {
        p.push_back(node);
        return;
    }
    if (node.startY < 0) {
        p.push_back(node);
        return;
    }
    if (node.startY > height()-1) {
        p.push_back(node);
        return;
    }
    for (Node& n : p){
        if (node.startX == n.startX && node.startY == n.startY) {
            if(!(node.name!=n.name&&n.onBridge == true)){
                p.push_back(node);
                return;
            }
        }
    }
    for (Node& n : nodeVector){
        if (n.name != '#') {
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
            if (node.startX == n.endX && node.startY == n.endY && node.name != n.name) {
                p.push_back(node);
                return;
            }
        }
        if(n.name == '#'){//bridge
            if (node.startX == n.startX&&node.startY == n.startY){
                onlyGoStraight = true;
                node.onBridge = true;
                break;
            }
        }
    }
    if (node.startX == node.endX && node.startY == node.endY){//got to the destination
        for (int i = 0; i < nodeVector.size(); ++i) {
            if (nodeVector[i].name == node.name){
                nodeVector[i].paths.push_back(p);
                break;
            }
        }
        if (nodeIndex==targetNodes.size()-1){//the last targetnode
            allSolutionVector.push_back(p);
        } else {
            getAllValidStrategies(p,nodeIndex+1);
        }
        p.push_back(node);
        return;
    }

    p.push_back(node);
    node.onBridge = false;

    if (onlyGoStraight){
        allSolutionHelperLeft(p,node,nodeIndex);
        node.startX++;
        p.pop_back();
    } else{
        allSolutionHelperUp(p,node,nodeIndex);
        node.startY++;
        p.pop_back();
        allSolutionHelperDown(p,node,nodeIndex);
        node.startY--;
        p.pop_back();
        allSolutionHelperLeft(p,node,nodeIndex);
        node.startX++;
        p.pop_back();
    }
}
void Grid::allSolutionHelperRight(vector<Node>& p, Node& node, int nodeIndex) {
    node.startX++;

    bool onlyGoStraight = false;//crossing a bridge.
    if(node.startX > width()-1) {
        p.push_back(node);
        return;
    }
    if (node.startY < 0) {
        p.push_back(node);
        return;
    }
    if (node.startY > height()-1) {
        p.push_back(node);
        return;
    }
    for (Node& n : p){
        if (node.startX == n.startX && node.startY == n.startY) {
            if(!(node.name!=n.name&&n.onBridge == true)){
                p.push_back(node);
                return;
            }
        }
    }
    for (Node& n : nodeVector){
        if(n.name != '#') {
            if (node.startX == n.startX && node.startY == n.startY) {
                p.push_back(node);
                return;
            }
            if (node.startX == n.endX && node.startY == n.endY && node.name != n.name) {
                p.push_back(node);
                return;
            }
        }
        if(n.name == '#'){//bridge
            if (node.startX == n.startX&&node.startY == n.startY){
                onlyGoStraight = true;
                node.onBridge = true;
                break;
            }
        }
    }

    if (node.startX == node.endX && node.startY == node.endY){//got to the destination
        for (int i = 0; i < nodeVector.size(); ++i) {
            if (nodeVector[i].name == node.name){
                nodeVector[i].paths.push_back(p);
                break;
            }
        }
        if (nodeIndex==targetNodes.size()-1){//the last targetnode
            allSolutionVector.push_back(p);
        } else {
            getAllValidStrategies(p,nodeIndex+1);
        }
        p.push_back(node);
        return;
    }

    p.push_back(node);
    node.onBridge = false;

    if (onlyGoStraight){
        allSolutionHelperRight(p,node,nodeIndex);
        node.startX--;
        p.pop_back();
    } else{
        allSolutionHelperUp(p,node,nodeIndex);
        node.startY++;
        p.pop_back();
        allSolutionHelperDown(p,node,nodeIndex);
        node.startY--;
        p.pop_back();
        allSolutionHelperRight(p,node,nodeIndex);
        node.startX--;
        p.pop_back();
    }
}


void Grid::getSolutionVector() {
    for (int i = 0; i < nodeVector.size(); ++i) {
        if (nodeVector[i].name != '#') {
            Node&n = nodeVector[i];
            targetNodes.push_back(n);
        }
    }

    occupiedPaths.clear();
    getAllValidStrategies(solutionpathVector,0);//MOST TIME CONSUMING s is the path point in n. O(s^n).

    for (int i = 0; i < allSolutionVector.size(); ++i) {
        vector<vector<Node>> solution;
        solutionPackedVector.push_back(solution);
        for (int j = 0; j < targetNodes.size(); ++j) {
            vector<Node> target;
            solutionPackedVector[i].push_back(target);
            for (int k = 0; k < allSolutionVector[i].size(); ++k) {
                if (allSolutionVector[i][k].name == targetNodes[j].name){
                    solutionPackedVector[i][j].push_back(allSolutionVector[i][k]);
                }
            }
        }
    }
}

void Grid::one_solution() {
    getSolutionVector();//setup all data
    if (solutionPackedVector.size()!=0) {
        horizontals.clear();
        verticals.clear();
        verticals = std::vector<std::string>(height() - 1, std::string(width(), ' '));
        horizontals = std::vector<std::string>(height(), std::string(width() - 1, ' '));
        for (int j = 0; j < targetNodes.size(); ++j) {
            vhConstructorForOCS(solutionPackedVector[0][j], &targetNodes[j]);
        }
        print();
        horizontals.clear();
        verticals.clear();
        verticals = std::vector<std::string>(height() - 1, std::string(width(), ' '));
        horizontals = std::vector<std::string>(height(), std::string(width() - 1, ' '));
    }else{
        print();
        cout<<endl <<"No Solutions"<<endl;
    }
}

void Grid::all_solutionWithCoveredBoard() {
    getSolutionVector();//setup all data.
    int maxGrid = height()*width();
    vector<Node> bridgeV;
    int numCoverboardSolutions = 0;
    int counter = 0;//number of intersection;
    if (allSolutionVector.size()!=0) {
        for (int i = 0; i < allSolutionVector.size(); ++i) {
            for (int k = 0; k < nodeVector.size(); ++k) {
                if (nodeVector[k].name == '#') {
                    int c = 0;
                    for (int j = 0; j < allSolutionVector[i].size(); ++j) {
                        if (nodeVector[k].startX == allSolutionVector[i][j].startX &&
                            nodeVector[k].startY == allSolutionVector[i][j].startY) {
                            c++;
                        }
                        if (c == 2) {
                            counter++;
                            break;
                        }
                    }
                }
            }
            /////////counter is getted
            if ((allSolutionVector[i].size() + targetNodes.size() * 2) - counter == maxGrid) {
                numCoverboardSolutions++;
                horizontals.clear();
                verticals.clear();
                verticals = std::vector<std::string>(height() - 1, std::string(width(), ' '));
                horizontals = std::vector<std::string>(height(), std::string(width() - 1, ' '));
                for (int j = 0; j < targetNodes.size(); ++j) {
                    vhConstructorForOCS(solutionPackedVector[i][j], &targetNodes[j]);
                }
                print();
                horizontals.clear();
                verticals.clear();
                verticals = std::vector<std::string>(height() - 1, std::string(width(), ' '));
                horizontals = std::vector<std::string>(height(), std::string(width() - 1, ' '));
            }
            counter = 0;
        }
        cout << endl;
        cout << "Found " << numCoverboardSolutions << " Solution(s)" << endl;
    } else{
        print();
        cout <<endl << "Found No Solutions" <<endl;
    }

}

void Grid::one_solutionWithCoveredBoard() {
    getSolutionVector();//setup all data.
    int maxGrid = height()*width();
    vector<Node> bridgeV;
    int counter = 0;//number of intersection;
    if (allSolutionVector.size()!=0) {
        for (int i = 0; i < allSolutionVector.size(); ++i) {
            for (int k = 0; k < nodeVector.size(); ++k) {
                if (nodeVector[k].name == '#') {
                    int c = 0;
                    for (int j = 0; j < allSolutionVector[i].size(); ++j) {
                        if (nodeVector[k].startX == allSolutionVector[i][j].startX &&
                            nodeVector[k].startY == allSolutionVector[i][j].startY) {
                            c++;
                        }
                        if (c == 2) {
                            counter++;
                            break;
                        }
                    }
                }
            }
            /////////counter is getted
            if ((allSolutionVector[i].size() + targetNodes.size() * 2) - counter == maxGrid) {
                horizontals.clear();
                verticals.clear();
                verticals = std::vector<std::string>(height() - 1, std::string(width(), ' '));
                horizontals = std::vector<std::string>(height(), std::string(width() - 1, ' '));
                for (int j = 0; j < targetNodes.size(); ++j) {
                    vhConstructorForOCS(solutionPackedVector[i][j], &targetNodes[j]);
                }
                print();
                horizontals.clear();
                verticals.clear();
                verticals = std::vector<std::string>(height() - 1, std::string(width(), ' '));
                horizontals = std::vector<std::string>(height(), std::string(width() - 1, ' '));
                break;
            }
            counter = 0;
        }
    } else{
        print();
        cout<<endl << "No Solutions" <<endl;
    }
}