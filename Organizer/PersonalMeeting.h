#pragma once
#include"Event.h"

class PersonalMeeting :public Event
{
	string name;
	string reason;
public:
	PersonalMeeting();
	PersonalMeeting(int d, int m, int y, int t_h, int t_m, const string& i, int dr, const string& pn, const string& n, const string& r);
	~PersonalMeeting();
	string getName()const;
	void setName(const string& n);
	string getReason()const;
	void setReason(const string& r);
	void print()const override;
	void input()override;
	friend ostream& operator<<(ostream& os, const PersonalMeeting& obj);
	friend istream& operator>>(istream& is, PersonalMeeting& obj);
};

