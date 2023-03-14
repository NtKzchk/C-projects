#include "Event.h"

Event::Event() = default;

Event::Event(int d, int m, int y, int t_h, int t_m, const string& i, int dr, const string& pn)
{
	time_t today_time = time(0);
	int today_d = localtime(&today_time)->tm_mday;
	int today_m = localtime(&today_time)->tm_mon + 1;
	int today_y = localtime(&today_time)->tm_year + 1900;
	if (y <= today_y && m <= today_m && d <= today_d)
		throw invalid_argument("Date can not be less than current");
	if (y == today_y && m < today_m)
		throw invalid_argument("Date can not be less than current");
	if (m > 12 || m <= 0 || y < today_y || t_h >= 24 || t_h < 0 || t_m >=60 || t_m < 0 || dr > 6 || dr < 1)
		throw invalid_argument("Error with time or date");
	if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && (d > 31 || d <= 0))
		throw invalid_argument("In January, March, May, July, August, October and December can not be more than 31 days or less 1 day");
	if ((m == 4 || m == 6 || m == 9 || m == 11) && (d > 30 || d <= 0))
		throw invalid_argument("In April, June, September, November can not be more than 31 days or less 1 day");
	if (m == 2 && (d > 29 || d <= 0) && (y % 4 == 0 && y % 100 != 0) || (y % 100 == 0 && y % 400 == 0))
		throw invalid_argument("In Fedruary of leap year can not be more than 29 days or less than 1 day");
	else if (m == 2 && (d > 28 || d <= 0))
		throw invalid_argument("In Fedruary of normal year can not be more than 28 days or less than 1 day");
	if (pn.empty())
		throw invalid_argument("Phone number can not be empty");
	if (i.empty())
		throw invalid_argument("Importance can not be empty");
	day = d;
	month = m;
	year = y;
	time_hour = t_h;
	time_minute = t_m;
	importance = str_to_importance(i);
	duration_in_hour = dr;
	phone_num = pn;
}

Event::~Event() = default;

int Event::getDay() const
{
	return day;
}

void Event::setDay(int d)
{
	day = d;
}

int Event::getMonth() const
{
	return month;
}

void Event::setMonth(int m)
{
	month = m;
}

int Event::getYear() const
{
	return year;
}

void Event::setYear(int y)
{
	year = y;
}

int Event::getHour() const
{
	return time_hour;
}

int Event::getMinute() const
{
	return time_minute;
}

string Event::getTime() const
{
	return to_string(time_hour) + ":" + to_string(time_minute);
}

void Event::setTime(int t_h, int t_m)
{
	time_hour = t_h;
	time_minute = t_m;
}

string Event::getImportance() const
{
	return importance_to_str(importance);
}

void Event::setImportance(const string& i)
{
	importance = str_to_importance(i);
}

int Event::getDuration_in_hour() const
{
	return duration_in_hour;
}

void Event::setDuration_in_hour(int d)
{
	duration_in_hour = d;
}

string Event::getPhone_num() const
{
	return phone_num;
}

void Event::setPhone_num(const string& pn)
{
	phone_num = pn;
}

Event::Importance Event::str_to_importance(const string& i)
{
	if (i == "Low")
		return Low;
	else if (i == "Medium")
		return Medium;
	else if (i == "High")
		return High;
	else
		return Unknown;
}

string Event::importance_to_str(Importance i)
{
	switch (i)
	{
	case Low:
		return "Low";
	case Medium:
		return "Medium";
	case High:
		return "High";
	}
	return "Unknown";
}

void Event::draw_text(Importance i)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (i == High)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	else if (i == Medium)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_RED);
	else if (i == Low)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
}

