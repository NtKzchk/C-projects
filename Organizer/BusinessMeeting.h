#pragma once
#include"Event.h"

class BusinessMeeting :public Event
{
	string f_name;
	string l_name;
public:
	BusinessMeeting();
	BusinessMeeting(int d, int m, int y, int t_h, int t_m, const string& i, int dr, const string& pn, const string& f_n, const string& l_n);
	~BusinessMeeting();
	string getF_name()const;
	void setF_name(const string& f_n);
	string getL_name()const;
	void setL_name(const string& l_n);
	void print()const override;
	void input()override;
	friend ostream& operator<<(ostream& os, const BusinessMeeting& obj);
	friend istream& operator>>(istream& is, BusinessMeeting& obj);
};



