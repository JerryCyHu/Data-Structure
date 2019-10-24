#include <iostream>
#include <string>
#include <cassert>
#include "provided_grid.h"


int main(int argc, char* argv[]) {

  std::string filename;

  // default behavior
  bool one_solution = true;

  // other options
  char color = ' ';
  bool one_color = false;
  bool all_paths = false;
  bool all_solutions = false;
  bool covers_board = false;

  
  // =======================================
  // FIRST:  Parse the arguments
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == std::string("--one_color")) {
      // the next argument is the color
      i++;
      assert (i < argc);
      assert (std::string(argv[i]).size() == 1);
      color = argv[i][0];
      one_color = true;
      one_solution = false;
      assert (all_paths == false && all_solutions == false && covers_board == false);
    } else if (std::string(argv[i]) == std::string("--all_paths")) {
      one_solution = false;
      all_paths = true;
      assert (one_color == false && all_solutions == false && covers_board == false);
    } else if (std::string(argv[i]) == std::string("--all_solutions")) {
      one_solution = false;
      all_solutions = true;
      assert (one_color == false && all_paths == false);
    } else if (std::string(argv[i]) == std::string("--covers_board")) {
      covers_board = true;
      assert (one_color == false && all_paths == false);
    } else {
      // must be the name of the file
      assert (filename == "");
      filename = argv[i];
    }
  }

  
  // =======================================
  // NEXT:  Load the puzzle file
  if (filename == "") {
    std::cerr << "ERROR!  Missing the filename" << std::endl;
    exit(0);
  }
  Grid a(filename);


  // =======================================
  // FINALLY:  SOLVE & PRINT -- this is placeholder code

  if(one_color){
      a.one_color_solution(color);
  } else if(all_paths){
      a.all_paths_solution();
  } else if(all_solutions){
      if (covers_board){
          a.all_solutionWithCoveredBoard();
      }else{
          a.all_solutions();
      }
  }else if(one_solution){
      if (covers_board){
          a.one_solutionWithCoveredBoard();
      }else {
          a.one_solution();
      }
  }

}
