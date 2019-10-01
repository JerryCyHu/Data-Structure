#include<iostream>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include"playerData.h"
#include<algorithm>
using namespace std;

PlayerData::PlayerData(string n) {
	team = "";
	name = n;
	goals = 0;
	assists = 0;
	penalties = 0;
}

string PlayerData::getTeam()const {
	return team;
}
string PlayerData::getName()const {
	return name;
}
int PlayerData::setTeam(string str) {
	team = str;
	return 0;
}
int PlayerData::getGoals() const {
	return goals;
}
int PlayerData::addGoals(int n) {
	goals += n;
	return 0;
}
int PlayerData::getAssists() const {
	return assists;
}
int PlayerData::addAssists(int n) {
	assists += n;
	return 0;
}
int PlayerData::getPenalties() const {
	return penalties;
}
int PlayerData::addPenalties(int n) {
	penalties += n;
	return 0;
}

bool sortPlayer(const PlayerData& left, const PlayerData& right) {
	if ((left.getGoals() + left.getAssists()) > (right.getGoals() + right.getAssists())) {
		return true;
	}
	else if ((left.getGoals() + left.getAssists()) == (right.getGoals() + right.getAssists())&& (left.getPenalties() < right.getPenalties()))
	{
		return true;
	}
	else if ((left.getGoals() + left.getAssists()) == (right.getGoals() + right.getAssists()) && (left.getPenalties() == right.getPenalties())&&(left.getName()<right.getName()))
	{
		return true;
	}
	else
	{
		return false;
	}

	//return (left.getGoals() + left.getAssists()) > (right.getGoals() + right.getAssists()) || (left.getGoals() + left.getAssists()) == (right.getGoals() + right.getAssists()) && (left.getPenalties() > right.getPenalties()) || (left.getGoals() + left.getAssists()) == (right.getGoals() + right.getAssists()) && (left.getPenalties() == right.getPenalties()) && (left.getName() < right.getName());
}