//
// PROVIDED CODE FOR HOMEWORK 4: GROCERY LISTS
// 
// You may use none, a little, or all of this, as you choose, but we
// strongly urge you to examine it carefully.  You may modify this
// code as you wish to complete the assignment.
//


#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include "recipe.h"
#include "ingredient.h"
#include "kitchen.h"
using namespace std;

// Helper functions
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes);
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes);
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen);

// The main loop parses opens the files for I/O & parses the input
int main(int argc, char* argv[]) {

  // Check the number of arguments.
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  // Open and test the input file.
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // Open and test the output file.
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // the kitchen & recipe list
  Kitchen kitchen;
  std::list<Recipe> recipes;

  // some variables to help with parsing
  char c;
  while (istr >> c) {
    if (c == 'r') {
      // READ A NEW RECIPE
      readRecipe(istr,ostr,recipes);

    } else if (c == 'a') {
      // ADD INGREDIENTS TO THE KITCHEN
      addIngredients(istr,ostr,kitchen);

    } else if (c == 'p') {
      // PRINT A PARTICULAR RECIPE
      printRecipe(istr,ostr,recipes);

    } else if (c == 'm') {
      // MAKE SOME FOOD
      makeRecipe(istr,ostr,recipes,kitchen);

    } else if (c == 'k') {
      // PRINT THE CONTENTS OF THE KITCHEN
      kitchen.printIngredients(ostr);

    } else {
      std::cerr << "unknown character: " << c << std::endl;
      exit(0);
    }
  }  

}


void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes) {
  int units;
  string name, name2;  
  istr >> name;
  // build the new recipe
  bool doesExist = false;
  for (Recipe r : recipes) {
	  if (r.getName() == name) {
		  doesExist = true;
	  }
  }
  if (doesExist == false) {
	  Recipe r(name);
	  while (1) {
		  istr >> units;
		  if (units == 0) break;
		  assert(units > 0);
		  istr >> name2;
		  r.addIngredient(name2, units);
	  }
	  // add it to the list
	  recipes.push_back(r);
	  ostr << "Recipe for " << name << " added" << std::endl;
  }
  else
  {
	  ostr << "Recipe for " << name << " already exists\n";
	  while (1) {
		  istr >> units;
		  if (units == 0) break;
		  istr >> name2;
	  }
  }
}


void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen) {
  int units;
  std::string name;
  int count = 0;
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name;
    // add the ingredients to the kitchen
    kitchen.addIngredient(name,units);
    count++;
  }

  if (count == 1)
	  ostr << count << " ingredient added to kitchen" << std::endl;
  else
	  ostr << count << " ingredients added to kitchen" << std::endl;
}


void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes) {
  std::string name;
  istr >> name;
  bool exist = false;

  for (const Recipe& r : recipes) {
	  if (r.getName() == name) {
		  r.printIngredients(ostr);
		  exist = true;
	  }
  }

  if (exist == false) {
	  ostr << "No recipe for " << name << endl;
  }




}


void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen) {
  std::string name;
  istr >> name;

  bool exist = false;
  bool ableToMake = true;
  list<Ingredient> insufficientList;

  for (const Recipe& r : recipes) { // check insufficiency
	  if (r.getName() == name) {
		  for (const Ingredient& iForR : r.getiList())
		  {
			  
				  bool ingreNoExist = true;
				  for (Ingredient& iForK : kitchen.iStore) {
					  if (iForR.getName() == iForK.getName()) {
						  ingreNoExist = false;
						  if (iForR.getSum() > iForK.getSum()) {
							  Ingredient ing = Ingredient(iForR.getName(), iForR.getSum() - iForK.getSum());
							  insufficientList.push_back(ing);
							  ableToMake = false;
						  }
					  }
				  }
				  if (ingreNoExist == true) {//ingredient does not exist
					  Ingredient ing = Ingredient(iForR.getName(), iForR.getSum());
					  insufficientList.push_back(ing);
				  }
			  
		  }
		  exist = true;
	  }
  }


  if (exist == false) {
	  ostr << "Don't know how to make " << name << endl;
  }
  else
  {
	  if (insufficientList.empty()) {//print out
		  for (const Recipe& r : recipes) { // check insufficiency
			  if (r.getName() == name) {
				  for (const Ingredient& iForR : r.getiList())
				  {
					  for (Ingredient& iForK : kitchen.iStore) {
						  if (iForR.getName() == iForK.getName()) {
							  iForK.addSum(-iForR.getSum());
						  }
					  }
				  }
			  }
		  }
		  ostr << "Made " << name <<endl;
	  }
	  else
	  {
		  insufficientList.sort(sortIngr2);
		  ostr << "Cannot make " << name << ", need to buy:\n";
		  for (Ingredient i : insufficientList)
		  {
			  if (i.getSum() == 1)
				  ostr << "  " << i.getSum() << " unit of " << i.getName() << endl;
			  else
				  ostr << "  " << i.getSum() << " units of " << i.getName() << endl;
		  }
	  }

  }

  for (list<Ingredient>::iterator itr = (kitchen.iStore.begin()); itr != kitchen.iStore.end(); ++itr)//wipe the 0 sum one
  {
	  if ((*itr).getSum() == 0) {
		  itr = kitchen.iStore.erase(itr);
	  }
  }





}


