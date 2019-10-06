#ifndef __recipe_h_
#define __recipe_h_
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
#include "ingredient.h"
using namespace std;

class Recipe
{
public:
	//constructor
	Recipe();
	Recipe(string rName);//the constructor which is used. rName stands for recipe's Name
	~Recipe();

	//functions
	void addIngredient(string ingredientsName, int num);// num is the number of ingredients which is going to be added
	string getName() const{
		return recipeName;
	}
	void printIngredients(ostream& ostr) const;//ostr for file writing
	list<Ingredient> getiList() const{//accessing iList
		return iList;
	}

private:
	string recipeName;
	list<Ingredient> iList;//store's ingredients
};

Recipe::Recipe()
{
}

Recipe::Recipe(string rName) {
	recipeName = rName;
}

Recipe::~Recipe()
{
}

void Recipe::addIngredient(string ingredientsName, int num) {
	bool alreadyExist = false;
	for (Ingredient&i : iList) {
		if (i.getName() == ingredientsName) {//matching name
			i.addSum(num);
			alreadyExist = true;
		}
	}
	if (alreadyExist == false) {//if not exist, add to iList
		Ingredient ingr = Ingredient(ingredientsName, num);
		iList.push_back(ingr);
	}
	iList.sort(sortIngr2);
}

void Recipe::printIngredients(ostream& ostr) const {
	ostr << "To make " << recipeName << ", mix together:\n";
	for (Ingredient i : iList) {
		if (i.getSum() == 1)
			ostr << "  " << i.getSum() << " unit of " << i.getName() <<endl;
		else
			ostr << "  " << i.getSum() << " units of " << i.getName() <<endl;
	}
}

#endif