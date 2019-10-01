#ifndef __time_h_
#define __time_h_
#include<iostream>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

class Time
{
public:
	Time();
	Time(int h, int m, int s);
	Time(const Time& obj);
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	int setHour(int i);
	int setMinute(int i);
	int setSecond(int i);
	string PrintAMPM();
private:
	int hour;
	int minute;
	int second;

};

bool IsEarlierThan(const Time& t1, const Time& t2);

#endif