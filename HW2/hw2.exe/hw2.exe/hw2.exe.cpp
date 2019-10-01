// hw2.exe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include<iomanip>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include"schoolData.h"
#include"playerData.h"
#include <iterator>
#include<algorithm>
using namespace std;

vector<SchoolData> schoolsList;
vector<PlayerData> playersList;
vector<string> contentVector;//Match Content!!!   IN HERE

int signInPlayer() {
	for (const string& str : contentVector) {
		if (str == "goal") {
			bool alreadySigned = false;
			for (PlayerData& p : playersList)
			{
				if (p.getName() == contentVector[(&str-&contentVector[0]) + 1] && p.getTeam()==contentVector[(&str - &contentVector[0]) - 1]) {
					alreadySigned = true;
					p.addGoals(1);
				}
			}
			if (!alreadySigned) {
				PlayerData player(contentVector[(&str - &contentVector[0]) + 1]);
				player.addGoals(1);
				player.setTeam(contentVector[(&str - &contentVector[0]) - 1]);
				playersList.push_back(player);
			}
			alreadySigned = false;
		}
		////////////////////////////////////////////
		if (str == "(") {
			bool alreadySigned = false;
			for (int i = 1; contentVector[(&str - &contentVector[0]) + i] != ")"; i++) {
				for (PlayerData& p : playersList)
				{
					if (p.getName() == contentVector[(&str - &contentVector[0]) + i] && p.getTeam() == contentVector[(&str - &contentVector[0]) - 3]) {
						alreadySigned = true;
						p.addAssists(1);
					}
				}
				if (!alreadySigned) {
					PlayerData player(contentVector[(&str - &contentVector[0]) + i]);
					player.addAssists(1);
					player.setTeam(contentVector[(&str - &contentVector[0]) - 3]);
					playersList.push_back(player);
				}
				alreadySigned = false;
			}
		}
		///////////////////////////////////////////
		if (str == "penalty") {
			if (contentVector[(&str - &contentVector[0]) + 1] != "BENCH") {
				bool alreadySigned = false;
				for (PlayerData& p : playersList)
				{
					if (p.getName() == contentVector[(&str - &contentVector[0]) + 1] && p.getTeam() == contentVector[(&str - &contentVector[0]) - 1]) {
						alreadySigned = true;
						p.addPenalties(1);
					}
				}
				if (!alreadySigned) {
					PlayerData player(contentVector[(&str - &contentVector[0]) + 1]);
					player.addPenalties(1);
					player.setTeam(contentVector[(&str - &contentVector[0]) - 1]);
					playersList.push_back(player);
				}
				alreadySigned = false;
			}
		}
	}
	cout << "";
	return 0;
}

///////////////////////////////////////////////////////////////

int signInSchools() {
	for (int i = 0; i < contentVector.size(); i++)
	{
		if (contentVector[i] == "at" || contentVector[i] == "vs.") {
			bool alreadySigned1 = false;
			bool alreadySigned2 = false;
			for  (SchoolData p : schoolsList)
			{
				if (p.getSchoolName() == contentVector[i - 1]){
					alreadySigned1 = true;
					}
				if (p.getSchoolName() == contentVector[i + 1]) {
					alreadySigned2 = true;
				}
			}
			if (!alreadySigned1) {
				SchoolData school(contentVector[i - 1]);
					schoolsList.push_back(school);
					//cout << school.getSchoolName()<<endl;
			}
			if (!alreadySigned2) {
				SchoolData school(contentVector[i + 1]);
				schoolsList.push_back(school);
				//cout << school.getSchoolName() << endl;
			}
			alreadySigned1 = false;
			alreadySigned2 = false;

		}
	}
	return 0;
}

int setWinsTiesLoses() {
		for (string& c : contentVector)
		{
			//cout << c;
			if (c == "FINAL") {
				//cout << "!!";
				for (SchoolData& s : schoolsList) {
					/////////////////=/////////////////////
					if (s.getSchoolName() == contentVector[(&c - &contentVector[0]) + 1]) {
						s.addGoals(atoi(contentVector[(&c - &contentVector[0]) + 2].c_str()));
						if (contentVector[(&c - &contentVector[0]) + 2] == contentVector[(&c - &contentVector[0]) + 4]) {
							s.addTies(1);
						}
						else if (contentVector[(&c - &contentVector[0]) + 2] > contentVector[(&c - &contentVector[0]) + 4]) {
							s.addWins(1);
						}
						else if (contentVector[(&c - &contentVector[0]) + 2] < contentVector[(&c - &contentVector[0]) + 4]) {
							s.addLoses(1);
						}
					}
					else if (s.getSchoolName() == contentVector[(&c - &contentVector[0]) + 3]) {
						s.addGoals(atoi(contentVector[(&c - &contentVector[0]) + 4].c_str()));
						if (contentVector[(&c - &contentVector[0]) + 2] == contentVector[(&c - &contentVector[0]) + 4]) {
							s.addTies(1);
						}
						else if (contentVector[(&c - &contentVector[0]) + 2] > contentVector[(&c - &contentVector[0]) + 4]) {
							s.addLoses(1);
						}
						else if (contentVector[(&c - &contentVector[0]) + 2] < contentVector[(&c - &contentVector[0]) + 4]) {
							s.addWins(1);
						}
					}
				}
			}
		}
	return 0;
}

int sumUpPenalties() {
	for (string& c : contentVector) {
		if (c == "penalty") {
			for (SchoolData& s : schoolsList) {
				if (s.getSchoolName() == contentVector[(&c - &contentVector[0]) - 1]) {
					s.addPenalties(1);
				}
			}
		}
	}
	//cout << schoolsList[1].getPenalties();
	return 0;
}

int analyzingWinPercentage() {
	for (SchoolData& s : schoolsList)
	{
		s.setWinPercentage();
		//cout << s.getWinPercentage()<<endl;
	}
	return 0;
}

int player_stats(string outputName) {
	ofstream file;
	file.open(outputName, ofstream::out | ofstream::trunc);
	int longestName = 0;
	int longestTeamName = 0;
	int longestGoals = 0;
	int longestAssists = 0;
	int longestPenalties = 0;
	for (const PlayerData& ply : playersList) {
		if (ply.getName().length() > longestName) {
			longestName = ply.getName().length();
		}
		if (ply.getTeam().length() > longestTeamName) {
			longestTeamName = ply.getTeam().length();
		}
		if (to_string(ply.getGoals()).length() > longestGoals) {
			longestGoals = to_string(ply.getGoals()).length();
		}
		if (to_string(ply.getAssists()).length() > longestAssists) {
			longestAssists = to_string(ply.getAssists()).length();
		}
		if (to_string(ply.getPenalties()).length() > longestPenalties) {
			longestPenalties = to_string(ply.getPenalties()).length();
		}
	}
	///////////////////
	cout << "Player Name";
	file << "Player Name";
	for (int i = 1; i <= longestName; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "Team";
	file << "Team";
	for (int i = 1; i <= longestTeamName+longestGoals; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "Goals";
	file << "Goals";
	for (int i = 1; i <= longestAssists; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "Assists";
	file << "Assists";
	for (int i = 1; i <= longestPenalties; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "Penalties";
	file << "Penalties";
	cout << endl;
	file << endl;
	///////////////////
	for (PlayerData ply : playersList) {
		cout << ply.getName();
		file << ply.getName();
		for (int i = 1; i <= longestName - ply.getName().length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << "           ";
		file << "           ";
		cout << ply.getTeam();
		file << ply.getTeam();
		for (int i = 1; i <= longestTeamName - ply.getTeam().length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		for (int i = 1; i <= longestGoals - to_string(ply.getGoals()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << "         ";
		file << "         ";
		cout << ply.getGoals();
		file << ply.getGoals();
		cout << "       ";
		file << "       ";
		for (int i = 1; i <= longestAssists - to_string(ply.getAssists()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << ply.getAssists();
		file << ply.getAssists();
		for (int i = 1; i <= longestPenalties - to_string(ply.getPenalties()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << "         ";
		file << "         ";
		cout << ply.getPenalties();
		file << ply.getPenalties();
		cout << endl;
		file << endl;
	}
	file.close();

	return 0;
}

int printTeam_stats(string outputName) {
	ofstream file;
	file.open(outputName, ofstream::out | ofstream::trunc);
	int longestSchoolName = 0;
	int longestWins = 0;
	int longestLoses = 0;
	int longestTies = 0;
	int longestGoals = 0;
	int longestPenalties = 0;
	for (const SchoolData&sch : schoolsList) {
		if (sch.getSchoolName().length() > longestSchoolName) {
			longestSchoolName = sch.getSchoolName().length();
		}
		if (sch.getWins() > longestWins) {
			longestWins = sch.getWins();
		}
		if (sch.getLoses() > longestLoses) {
			longestLoses = sch.getLoses();
		}
		if (sch.getTies() > longestTies) {
			longestTies = sch.getTies();
		}
		if (sch.getGoals() > longestGoals) {
			longestGoals = sch.getGoals();
		}
		if (sch.getPenalties() > longestPenalties) {
			longestPenalties = sch.getPenalties();
		}
	}
	int a = 0;
	while (longestWins>0)
	{
		longestWins /= 10;
		a++;
	}
	longestWins = a;
	a = 0;
	while (longestLoses > 0)
	{
		longestLoses /= 10;
		a++;
	}
	longestLoses = a;
	a = 0;
	while (longestTies > 0)
	{
		longestTies /= 10;
		a++;
	}
	longestTies = a;
	a = 0;
	while (longestGoals > 0)
	{
		longestGoals /= 10;
		a++;
	}
	longestGoals = a;
	a = 0;
	while (longestPenalties > 0)
	{
		longestPenalties /= 10;
		a++;
	}
	longestPenalties = a;
	a = 0;
	if (longestGoals == 0)
	{
		longestGoals = 1;
	}
	if (longestLoses == 0) {
		longestLoses = 1;
	}
	if (longestPenalties == 0) {
		longestPenalties = 1;
	}
	if (longestTies == 0) {
		longestTies = 1;
	}
	if (longestWins == 0) {
		longestWins = 1;
	}
	////////////////////////////
	cout << "Team Name";
	file << "Team Name";
	for (int i = 1; i <= longestSchoolName+longestWins; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "W";
	file << "W";
	for (int i = 1; i <= 4 + longestLoses - 1; i++) {
		cout << " ";
		file << " ";
	}
	cout << "L";
	file << "L";
	for (int i = 1; i <= 4 + longestTies - 1; i++) {
		cout << " ";
		file << " ";
	}
	cout << "T";
	file << "T";
	cout << "    Win%";
	file << "    Win%";
	for (int i = 1; i <= longestGoals; i++) {
		cout << " ";
		file << " ";
	}
	cout << "Goals";
	file << "Goals";
	for (int i = 1; i <= longestPenalties; i++) {
		cout << " ";
		file << " ";
	}
	cout << "Penalties";
	file << "Penalties";
	cout << endl;
	file << endl;
	for (SchoolData sch : schoolsList) {
		/////////////name
		cout << sch.getSchoolName();//doc
		file << sch.getSchoolName();		for (int i = 1; i <= longestSchoolName-sch.getSchoolName().length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << "          ";//doc
		file << "          ";
		///////////////////wins
		for (int i = 1; i <= longestWins - to_string(sch.getWins()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << sch.getWins();//doc
		file << sch.getWins();
		cout << "    ";//doc
		file << "    ";
		/////////////////loses
		for (int i = 1; i <= longestLoses - to_string(sch.getLoses()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << sch.getLoses();//doc
		file << sch.getLoses();
		cout << "    ";//doc
		file << "    ";
		//////////////////Ties
		for (int i = 1; i <= longestTies - to_string(sch.getTies()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << sch.getTies();//doc
		file << sch.getTies();
		cout << "    ";//doc
		file << "    ";
		///////////WinPercentage
		cout << fixed << setprecision(2) << sch.getWinPercentage();
		file << fixed << setprecision(2) << sch.getWinPercentage();
		cout << "     ";//doc
		file << "     ";
		////////////goals
		for (int i = 1; i <= longestGoals - to_string(sch.getGoals()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << sch.getGoals();
		file << sch.getGoals();
		cout << "         ";//doc
		file << "         ";
		///////////////penalties
		for (int i = 1; i <= longestPenalties - to_string(sch.getPenalties()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << sch.getPenalties();
		file << sch.getPenalties();
		cout << endl;
		file << endl;

	}
	file.close();
	return 0;
}

int custom_stats(string outputName) {
	vector<PlayerData> mvpVector;
	bool noExistTeamPlayer = true;
	for (PlayerData ply : playersList) {
		for (PlayerData & mvpPlayer : mvpVector) {
			if (ply.getTeam() == mvpPlayer.getTeam())
			{
				if (((float)ply.getGoals() + (float)ply.getAssists()) - (float)ply.getPenalties() > ((float)mvpPlayer.getGoals() + (float)mvpPlayer.getAssists()) - (float)mvpPlayer.getPenalties())
				{
					mvpPlayer = ply;
				}
				noExistTeamPlayer = false;
			}
		}
		if (noExistTeamPlayer == true) {
			mvpVector.push_back(ply);
		}
		noExistTeamPlayer = true;
	}
	///////////////////////
	ofstream file;
	file.open(outputName, ofstream::out | ofstream::trunc);
	int longestName = 0;
	int longestTeamName = 0;
	int longestGoals = 0;
	int longestAssists = 0;
	int longestPenalties = 0;
	for (const PlayerData& ply : mvpVector) {
		if (ply.getName().length() > longestName) {
			longestName = ply.getName().length();
		}
		if (ply.getTeam().length() > longestTeamName) {
			longestTeamName = ply.getTeam().length();
		}
		if (to_string(ply.getGoals()).length() > longestGoals) {
			longestGoals = to_string(ply.getGoals()).length();
		}
		if (to_string(ply.getAssists()).length() > longestAssists) {
			longestAssists = to_string(ply.getAssists()).length();
		}
		if (to_string(ply.getPenalties()).length() > longestPenalties) {
			longestPenalties = to_string(ply.getPenalties()).length();
		}
	}
	sort(mvpVector.begin(), mvpVector.end(), sortPlayer);
	///////////////////
	cout << "Player Name";
	file << "Player Name";
	for (int i = 1; i <= longestName; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "Team";
	file << "Team";
	for (int i = 1; i <= longestTeamName + longestGoals; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "Goals";
	file << "Goals";
	for (int i = 1; i <= longestAssists; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "Assists";
	file << "Assists";
	for (int i = 1; i <= longestPenalties; i++)
	{
		cout << " ";
		file << " ";
	}
	cout << "Penalties";
	file << "Penalties";
	cout << endl;
	file << endl;
	///////////////////
	for (PlayerData ply : mvpVector) {
		cout << ply.getName();
		file << ply.getName();
		for (int i = 1; i <= longestName - ply.getName().length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << "           ";
		file << "           ";
		cout << ply.getTeam();
		file << ply.getTeam();
		for (int i = 1; i <= longestTeamName - ply.getTeam().length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		for (int i = 1; i <= longestGoals - to_string(ply.getGoals()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << "         ";
		file << "         ";
		cout << ply.getGoals();
		file << ply.getGoals();
		cout << "       ";
		file << "       ";
		for (int i = 1; i <= longestAssists - to_string(ply.getAssists()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << ply.getAssists();
		file << ply.getAssists();
		for (int i = 1; i <= longestPenalties - to_string(ply.getPenalties()).length(); i++)
		{
			cout << " ";//doc
			file << " ";
		}
		cout << "         ";
		file << "         ";
		cout << ply.getPenalties();
		file << ply.getPenalties();
		cout << endl;
		file << endl;
	}
	file.close();
	return 0;
}

int main(int argc, char* argv[])
{
	string inputFileName = argv[1];
	string outputFileName = argv[2];
	string analyzeOptions = argv[3];
	int longestSchoolName;
	//string inputFileName = "2012_ecac.txt";
	//string outputFileName = "123.txt";
	//string analyzeOptions = "cool";
	ifstream fileDirectory(inputFileName.c_str());
	//string fileContent;
	//fileContent.assign(istreambuf_iterator<char>(fileDirectory), istreambuf_iterator<char>());
	//////////error part///////
	string line = "";
	while (fileDirectory >> line)
	{
		//cout << line<<"   ";
		contentVector.push_back(line);
	}
	///////////////////
	if (analyzeOptions == "--team_stats") {
		signInSchools();
		setWinsTiesLoses();
		sumUpPenalties();
		analyzingWinPercentage();
		sort(schoolsList.begin(), schoolsList.end(), sortSchool);
		printTeam_stats(outputFileName);
	}
	if (analyzeOptions == "--player_stats")
	{
		signInPlayer();
		sort(playersList.begin(), playersList.end(), sortPlayer);
		player_stats(outputFileName);
	}
	if (analyzeOptions == "--custom_stats")
	{
		signInPlayer();
		custom_stats(outputFileName);
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
