#include<iostream>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include"schoolData.h"
#include<algorithm>
using namespace std;

SchoolData::SchoolData(string name) {
	schoolName = name;
	wins = 0;
	loses = 0;
	ties = 0;
	penalties = 0;
	goals = 0;
	winPercentage = 0;
}

string SchoolData::getSchoolName() const {
	return schoolName;
}

int SchoolData::getTies() const {
	return ties;
}

int SchoolData::getWins() const {
	return wins;
}

int SchoolData::getLoses() const {
	return loses;
}

int SchoolData::getGoals() const {
	return goals;
}

int SchoolData::getPenalties() const{
	return penalties;
}

float SchoolData::getWinPercentage() const {
	return winPercentage;
}

int SchoolData::addGoals(int n) {
	goals += n;
	return 0;
}

int SchoolData::addPenalties(int n) {
	penalties += n;
	return 0;
}

int SchoolData::addTies(int n) {
	ties += n;
	return 0;
}

int SchoolData::addWins(int n) {
	wins += n;
	return 0;
}

int SchoolData::addLoses(int n) {
	loses += n;
	return 0;
}

int SchoolData::setWinPercentage() {
	float w = wins;
	float l = loses;
	float t = ties;
	winPercentage = (w + 0.5 * t) / (w + l + t);
	return 0;
}

bool sortSchool(const SchoolData& left, const SchoolData& right) {
	return (left.getWinPercentage() > right.getWinPercentage()) || ((left.getWinPercentage() == right.getWinPercentage()) && (left.getGoals() > right.getGoals())) || ((left.getWinPercentage() == right.getWinPercentage()) && (left.getGoals() == right.getGoals())&&left.getSchoolName() < right.getSchoolName());
}