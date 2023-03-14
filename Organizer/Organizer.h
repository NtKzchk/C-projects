#pragma once
#include"Birthday.h"
#include"BusinessMeeting.h"
#include"PersonalMeeting.h"
#include"VisitToSpecialist.h"

class Organizer
{
	string name_owner;
	vector<shared_ptr<Event>> arr;
public:
	Organizer();
	Organizer(const string& n);
	string getName_owner()const;
	void setName_owner(const string& n);
	void addEvent(const Birthday& obj);
	void addEvent(const BusinessMeeting& obj);
	void addEvent(const PersonalMeeting& obj);
	void addEvent(const VisitToSpecialist& obj);
	void delEvent(int d, int m, int y, int t_h, int t_m);
	void sortEvent_by_date_and_time();
	void sortEvent_by_importance();
	void searchEvent_by_importance(const string& i);
	void searchEvent_by_date(int d, int m, int y);
	void save_organizer_txt(const string& file_name);
	void load_organizer_txt(const string& file_name);
	void file_rename_txt(const char* old_name, const char* new_name);
	void file_remove_txt(const char* file_name);
	void print()const;
	void printToday()const;
	void printBirthday()const;
	void printBusinessMeeting()const;
	void printPersonalMeeting()const;
	void printVisitToSpecialist()const;
	void menu();
};
