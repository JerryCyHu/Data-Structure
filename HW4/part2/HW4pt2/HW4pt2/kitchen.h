#ifndef __kitchen_h_
#define __kitchen_h_
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "ingredient.h"

using namespace std;

class Kitchen
{
public:
	list<Ingredient> iStore;
	//constructor
	Kitchen();
	~Kitchen();

	//functions
	void printIngredients(ofstream &o);//print the ingredients. o is ostream(writing file)
	void addIngredient(string ingredientName, int num);//add ingredient to iStore. num is how many is going to add
	list<Ingredient> getiStore() const {
		return iStore;
	}

private:
};

Kitchen::Kitchen()
{
}

Kitchen::~Kitchen()
{
}

void Kitchen::addIngredient(string ingredientName, int num) {
	bool alreadyExist = false;
	for (Ingredient& i : iStore) {
		if (i.getName() == ingredientName) {//matching name
			i.addSum(num);
			alreadyExist = true;
		}
	}
	if (alreadyExist == false) {
		Ingredient ingr = Ingredient(ingredientName, num);
		iStore.push_back(ingr);
	}
}

void Kitchen::printIngredients(ofstream &o) {
	for (list<Ingredient>::iterator itr = (iStore.begin()); itr != iStore.end(); ++itr)//make sure to wipe the 0 sum one
	{
		if ((*itr).getSum() == 0) {
			itr = iStore.erase(itr);
		}
	}
	iStore.sort(sortIngr);
	o << "In the kitchen:\n";
	for (const Ingredient& i : iStore) {
		if (i.getSum() == 1)
			o << "  " << i.getSum() << " unit of " << i.getName() << endl;
		else
			o << "  " << i.getSum() << " units of " << i.getName() << endl;
	}
}
#endif