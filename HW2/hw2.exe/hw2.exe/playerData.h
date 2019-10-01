#ifndef __playerData_h_
#define __playerData_h_
#include<iostream>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class PlayerData
{
public:
	PlayerData(string n);
	string getTeam() const;
	string getName() const;
	int setTeam(string str);
	int getGoals() const;
	int addGoals(int n);
	int getAssists() const;
	int addAssists(int n);
	int getPenalties() const;
	int addPenalties(int n);
private:
	string team;
	string name;
	int goals;
	int assists;
	int penalties;
};

bool sortPlayer(const PlayerData& left, const PlayerData& right);

#endif