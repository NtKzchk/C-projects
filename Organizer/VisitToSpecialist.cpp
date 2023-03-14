#include "VisitToSpecialist.h"

VisitToSpecialist::VisitToSpecialist() = default;

VisitToSpecialist::VisitToSpecialist(int d, int m, int y, int t_h, int t_m, const string & i, int dr, const string & pn, const string& s, const string& f_n, const string& l_n) 
try:Event(d, m, y, t_h, t_m, i, dr, pn)
{
	if (s.empty())
		throw invalid_argument("Specialization can not be empty");
	if (f_n.empty())
		throw invalid_argument("First name can not be empty");
	if (l_n.empty())
		throw invalid_argument("Last name can not be empty");
	specialization = s;
	f_name = f_n;
	l_name = l_n;
}
catch (const invalid_argument& ex)
{
	cerr << "Error in class VisitToSpecialist. " << ex.what() << endl;
}

VisitToSpecialist::~VisitToSpecialist() = default;

string VisitToSpecialist::getSpecialization() const
{
	return specialization;
}

void VisitToSpecialist::setSpecialization(const string& s)
{
	specialization = s;
}

string VisitToSpecialist::getF_name() const
{
	return f_name;
}

void VisitToSpecialist::setF_name(const string& f_n)
{
	f_name = f_n;
}
string VisitToSpecialist::getL_name() const
{
	return l_name;
}
void VisitToSpecialist::setL_name(const string& l_n)
{
	l_name = l_n;
}
void VisitToSpecialist::print() const
{
	draw_text(importance);
	cout << "><><><><><>VISIT TO "<<specialization<<"<><><><><><" << endl;
	cout << day << "." << month << "." << year << endl;
	cout << "Time: " << time_hour << ":" << (time_minute == 0 ? "00" : time_minute < 10 ? "0" + to_string(time_minute) : to_string(time_minute)) << endl;
	cout << "Importance: " << importance_to_str(importance) << endl;
	cout << "Duration in hour: " << duration_in_hour << " hours" << endl;
	cout << f_name << " " << l_name << " -> " << phone_num << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void VisitToSpecialist::input()
{
	char buf[500];
	cout << "Enter information about Visit to specialist:" << endl;
	cout << "day->";
	cin >> day;
	cout << "month->";
	cin >> month;
	cout << "year->";
	cin >> year;
	cout << "time (for example 12:00, 16:09, 9:21)->";
	cin >> buf;
	time_hour = stoi(strtok(buf, ":,."));
	time_minute = stoi(strtok(NULL, ""));
	cout << "duration in hour(1-6 hour)->";
	cin >> duration_in_hour;

	time_t today_time = time(0);
	int today_d = localtime(&today_time)->tm_mday;
	int today_m = localtime(&today_time)->tm_mon + 1;
	int today_y = localtime(&today_time)->tm_year + 1900;
	if (year <= today_y && month <= today_m && day <= today_d)
		throw invalid_argument("Date can not be less than current");
	if (year == today_y && month < today_m)
		throw invalid_argument("Date can not be less than current");
	if (month > 12 || month <= 0 || year < today_y || time_hour >= 24 || time_hour < 0 || time_minute >= 60 || time_minute < 0 || duration_in_hour > 6 || duration_in_hour < 1)
		throw invalid_argument("Error with time or date");
	if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 31 || day <= 0))
		throw invalid_argument("In January, March, May, July, August, October and December can not be more than 31 days or less 1 day");
	if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30 || day <= 0))
		throw invalid_argument("In April, June, September, November can not be more than 31 days or less 1 day");
	if (month == 2 && (day > 29 || day <= 0) && (year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 400 == 0))
		throw invalid_argument("In Fedruary of leap year can not be more than 29 days or less than 1 day");
	else if (month == 2 && (day > 28 || day <= 0))
		throw invalid_argument("In Fedruary of normal year can not be more than 28 days or less than 1 day");

	cout << "Possible importance:" << endl;
	Importance im[]{ Unknown, Low, Medium, High };
	for (int i = 0; i < 4; i++)
	{
		cout << "-" << importance_to_str((im[i])) << endl;
	}
	cout << "importance->";
	cin >> buf;
	importance = str_to_importance(buf);
	cout << "phone number->";
	cin >> phone_num;
	cout << "doctor's specialization->";
	cin >> specialization;
	cout << "doctor's full name:" << endl;
	cout << "first name->";
	cin >> f_name;
	cout << "last name->";
	cin >> l_name;
}

ostream& operator<<(ostream& os, const VisitToSpecialist& obj)
{
	os << obj.day << "|" << obj.month << "|" << obj.year << "|" << obj.time_hour << "|" << obj.time_minute << "|" << obj.importance_to_str(obj.importance) << "|" << obj.duration_in_hour
		<< "|" << obj.phone_num << "|" << obj.specialization << "|" << obj.f_name << "|" << obj.l_name << "|";
	return os;
}

istream& operator>>(istream& is, VisitToSpecialist& obj)
{
	string buf;
	getline(is, buf, '|');
	if (buf.empty())
		return is;
	obj.day = stoi(buf);
	getline(is, buf, '|');
	obj.month = stoi(buf);
	getline(is, buf, '|');
	obj.year = stoi(buf);
	getline(is, buf, '|');
	obj.time_hour = stoi(buf);
	getline(is, buf, '|');
	obj.time_minute = stoi(buf);
	getline(is, buf, '|');
	obj.importance = obj.str_to_importance(buf);
	getline(is, buf, '|');
	obj.duration_in_hour = stoi(buf);
	getline(is, buf, '|');
	obj.phone_num = buf;
	getline(is, buf, '|');
	obj.specialization = buf;
	getline(is, buf, '|');
	obj.f_name = buf;
	getline(is, buf, '|');
	obj.l_name = buf;
	return is;
}
