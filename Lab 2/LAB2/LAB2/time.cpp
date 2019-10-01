#include<iostream>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include"time.h"
using namespace std;

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
	cout << "initialSet\n";
}

Time::Time(int h, int m, int s) {
	hour = h;
	minute = m;
	second = s;
	cout << "costumSet\n";
}

Time::Time(const Time& obj) {
	hour = obj.getHour();
	minute = obj.getMinute();
	second = obj.getSecond();
	cout << "copy\n";
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

string Time::PrintAMPM() {
	string h = "";
	string m = "";
	string s = "";
	string AMPM = "";
	if (hour<12)
	{
		//h = to_string(hour);
		AMPM = "AM";
		if (hour == 0) {
			cout << "12" << ":";
		}
		else
		{
			cout << hour << ":";
		}
	}
	else
	{
		//h = hour - 12;
		AMPM = "PM";
		if (hour-12 == 0) {
			cout << "12" << ":";
		}
		else
		{
			cout << hour-12 << ":";
		}
	}
	if (minute / 10 == 0) {
		//string o =to_string(minute);
		//m = "0" + o;
		cout << "0" << minute<<":";
	}
	else
	{
		//m = minute;
		cout << minute<<":";
	}
	if (second / 10 == 0) {
		//string o = to_string(second);
		//s = "0" + o;
		cout << "0" << second;
	}
	else
	{
		//s = second;
		cout << second;
	}
	cout << AMPM<<endl;
	return h + ":" + m + ":" + s;
}

int Time::setHour(int i) {
	hour = i;
	return 0;
}

int Time::setMinute(int i) {
	minute = i;
	return 0;
}

int Time::setSecond(int i) {
	second = i;
	return 0;
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
	if (t1.getHour()<t2.getHour()) {
		return true;
	}
	else if (t1.getHour() == t2.getHour() && t1.getMinute() < t2.getMinute()) {
		return true;
	}
	else if (t1.getHour() == t2.getHour() && t1.getMinute() == t2.getMinute() && t1.getSecond() < t2.getSecond()) {
		return true;
	}
	else if (t1.getHour() == t2.getHour() && t1.getMinute() == t2.getMinute() && t1.getSecond() == t2.getSecond()) {
		return true;
	}
	return false;
}