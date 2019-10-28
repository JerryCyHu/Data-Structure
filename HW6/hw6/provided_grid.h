#ifndef provided_grid_h
#define provided_grid_h
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

using namespace std;

class Grid {

public:

  // constructor loads the input puzzle board
  Grid (const std::string &filename);

  // simple accessors
  int width() { return endpoints[0].size(); }
  int height() { return endpoints.size(); }

  // print an ASCII art representation of the board
  void print();


  // A temporary hack to demonstrate how the print function works for solved boards
  void hardcoded_solution(const std::string &filename);

  // solution for one_color
  void one_color_solution(char name);

  // solution for all_paths. Will use one_color_solution's helper functions.
  void all_paths_solution();

  // solution for all_solutions
  void all_solutions();

  // solution for one_solution
  void one_solution();

  //solution for all_solution with covered board.
  void all_solutionWithCoveredBoard();

  //solution for one_solution with covered board
  void one_solutionWithCoveredBoard();

private:
    // a helper function to get all node's all paths.
    // Will be used in all_paths, one_solution and all_solution
    void getAllNodesAllPaths();

  // a helper function for print
  char print_center(int i, int j);

  // a helper for one_color_solution
  void oneColorHelperUp(vector<Node>& p, Node& node);
  void oneColorHelperDown(vector<Node>& p, Node& node);
  void oneColorHelperLeft(vector<Node>& p, Node& node);
  void oneColorHelperRight(vector<Node>& p, Node& node);

  // helpers for all_solution
  void allSolutionHelperUp(vector<Node>& p, Node& node, int nodeIndex);
  void allSolutionHelperDown(vector<Node>& p, Node& node, int nodeIndex);
  void allSolutionHelperLeft(vector<Node>& p, Node& node, int nodeIndex);
  void allSolutionHelperRight(vector<Node>& p, Node& node, int nodeIndex);

  //a helper for one_color_solution to construct V, H
  void vhConstructorForOCS(vector<Node>& p, Node* target);

  //a helper for getting all valid strategies
  void getAllValidStrategies(vector<Node>&solutionpathVector, int indexOfNodes);//indexOfNodes is the node that we are going to find solutions for
  vector<Node> targetNodes;//storing all target nodes
  vector<Node> occupiedPaths;//store all currently "valid" path into this vector

  //helper for all_solution, packed_all_solution and one_solution. Setup all the data
  void getSolutionVector();

  // a simple representation of the input puzzle
  std::vector<std::string> endpoints;

  // a representation of the solution paths
  //
  // NOTE note that the dimensions are off by one of the endpoints.
  // We have 1 fewer row of vertical path edges and 1 fewer column of
  // horizontal path edges.
  std::vector<std::string> verticals;
  std::vector<std::string> horizontals;

  vector<Node> nodeVector;//store nodes. 'A', 'B' ...etc or '#'(Wall)
  vector<Node> pathNodes;//a helper vector for helper function up down left right for one_color
  vector<Node> solutionpathVector;//a helper vector for helper function up down left right for all_solution
  //////////////for all nodes solution//////////
  vector<vector<Node>> allSolutionVector;//It stores all the strategy. The inner vector stores node's path detail. MinUnit: solution
  vector<vector<vector<Node>>> solutionPackedVector;//packed mode of allSolutionVector. MinUnit: target

};

#endif