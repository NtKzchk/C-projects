#pragma once
#include"Event.h"

class Birthday:public Event
{
	string birth_hum_f_name;
	string birth_hum_l_name;
public:
	Birthday();
	Birthday(int d, int m, int y, int t_h, int t_m, const string& i, int dr, const string& pn, const string& b_h_f_n, const string& b_h_l_n);
	~Birthday() override;
	string getBirth_hum_f_name()const;
	void setBirth_hum_f_name(const string& b_h_f_n);
	string getBirth_hum_l_name()const;
	void setBirth_hum_l_name(const string& b_h_l_n);
	void print()const override;
	void input()override;
	friend ostream& operator<<(ostream& os, const Birthday& obj);
	friend istream& operator>>(istream& is, Birthday& obj);
};

