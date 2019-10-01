#ifndef __schoolData_h_
#define __schoolData_h_
#include<iostream>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class SchoolData
{
public:
	SchoolData(string name);
	string getSchoolName() const;
	int getGoals() const;
	int addGoals(int n);
	int getPenalties() const;
	int addPenalties(int n);
	float getWinPercentage() const;
	int setWinPercentage();
	int getWins() const;
	int addWins(int n);
	int getLoses() const;
	int addLoses(int n);
	int getTies() const;
	int addTies(int n);
private:
	string schoolName;
	int wins;
	int loses;
	int ties;
	int penalties;
	int goals;
	float winPercentage;
};

bool sortSchool (const SchoolData& left, const SchoolData& right);

#endif