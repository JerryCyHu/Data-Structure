#ifndef __ingredient_h_
#define __ingredient_h_

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

//class for each ingredient
class Ingredient
{
public:
	//constructor
	Ingredient(string n, int s);
	~Ingredient();

	//functions
	void addSum(int s) {//add s more number of the ingredient
		sum += s;
	}

	string getName() const{//get the name of the ingredient
		return name;
	}

	int getSum() const {//get number of the ingredient
		return sum;
	}

private:
	string name;//ingredient's name
	int sum;//how many of this ingredient

};


Ingredient::Ingredient(string n, int s) {
	name = n;
	sum = s;
}

Ingredient::~Ingredient()
{
}

bool sortIngr(const Ingredient& left, const Ingredient& right) {//sort by sum first
	return left.getSum() < right.getSum() || (left.getSum() == right.getSum() && left.getName() < right.getName());
}

bool sortIngr2(const Ingredient& left, const Ingredient& right) {//sort by alphabet
	return left.getName() < right.getName();
}
#endif