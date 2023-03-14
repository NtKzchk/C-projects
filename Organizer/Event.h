#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<iostream>
#include<Windows.h>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<fstream>
#include<iterator>
#include<memory>
#include<ctime>
#include<io.h>
using namespace std;

class Event
{
public:
	enum Importance { Unknown, Low, Medium, High };
protected:
	int day = 0;
	int month = 0;
	int year = 0;
	int time_hour = 0;
	int time_minute = 0;
	Importance importance = Low;
	int duration_in_hour = 0;
	string phone_num;
public:
	Event();
	Event(int d, int m, int y, int t_h, int t_m, const string& i, int dr, const string& pn);
	virtual ~Event();
	int getDay()const;
	void setDay(int d);
	int getMonth()const;
	void setMonth(int m);
	int getYear()const;
	void setYear(int y);
	int getHour()const;
	int getMinute()const;
	string getTime()const;
	void setTime(int t_h, int t_m);
	string getImportance()const;
	void setImportance(const string& i);
	int getDuration_in_hour()const;
	void setDuration_in_hour(int d);
	string getPhone_num()const;
	void setPhone_num(const string& pn);
	virtual void input() = 0;
	virtual void print()const = 0;
	static Importance str_to_importance(const string& i);
	static string importance_to_str(Importance i);
	static void draw_text(Importance i);
};

