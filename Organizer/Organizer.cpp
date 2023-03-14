#include "Organizer.h"

Organizer::Organizer() = default;

Organizer::Organizer(const string& n)
try
{
	if (n.empty())
		throw invalid_argument("Owner's name can not be empty");
	name_owner = n;
}
catch (const invalid_argument& ex)
{
	cerr << "Error in class Organizer." << ex.what() << endl;
}

string Organizer::getName_owner() const
{
	return name_owner;
}

void Organizer::setName_owner(const string& n)
{
	name_owner = n;
}

void Organizer::addEvent(const Birthday& obj)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (obj.getYear() == arr[i]->getYear() && obj.getMonth() == arr[i]->getMonth() && obj.getDay() == arr[i]->getDay())
		{
			if (obj.getHour() == arr[i]->getHour() && obj.getMinute() == arr[i]->getMinute())
			{
				cout << "This day and time are busy." << endl;
				return;
			}
			else if (obj.getHour() < arr[i]->getDuration_in_hour() + arr[i]->getHour() && arr[i]->getMinute() > obj.getMinute())
			{
				cout << "This day and time are busy." << endl;
				return;
			}
		}
	}
	arr.push_back(make_shared<Birthday>(obj));
}

void Organizer::addEvent(const BusinessMeeting& obj)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (obj.getYear() == arr[i]->getYear() && obj.getMonth() == arr[i]->getMonth() && obj.getDay() == arr[i]->getDay())
		{
			if (obj.getHour() == arr[i]->getHour() && obj.getMinute() == arr[i]->getMinute())
			{
				cout << "This day and time are busy." << endl;
				return;
			}
			else if (obj.getHour() < arr[i]->getDuration_in_hour() + arr[i]->getHour() && arr[i]->getMinute() > obj.getMinute())
			{
				cout << "This day and time are busy." << endl;
				return;
			}
		}
	}
	arr.push_back(make_shared<BusinessMeeting>(obj));
}

void Organizer::addEvent(const PersonalMeeting& obj)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (obj.getYear() == arr[i]->getYear() && obj.getMonth() == arr[i]->getMonth() && obj.getDay() == arr[i]->getDay())
		{
			if (obj.getHour() == arr[i]->getHour() && obj.getMinute() == arr[i]->getMinute())
			{
				cout << "This day and time are busy." << endl;
				return;
			}
			else if (obj.getHour() < arr[i]->getDuration_in_hour() + arr[i]->getHour() && arr[i]->getMinute() > obj.getMinute())
			{
				cout << "This day and time are busy." << endl;
				return;
			}
		}
	}
	arr.push_back(make_shared<PersonalMeeting>(obj));
}

void Organizer::addEvent(const VisitToSpecialist& obj)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (obj.getYear() == arr[i]->getYear() && obj.getMonth() == arr[i]->getMonth() && obj.getDay() == arr[i]->getDay())
		{
			if (obj.getHour() == arr[i]->getHour() && obj.getMinute() == arr[i]->getMinute())
			{
				cout << "This day and time are busy." << endl;
				return;
			}
			else if (obj.getHour() < arr[i]->getDuration_in_hour() + arr[i]->getHour() && arr[i]->getMinute() > obj.getMinute())
			{
				cout << "This day and time are busy." << endl;
				return;
			}
		}
	}
	arr.push_back(make_shared<VisitToSpecialist>(obj));
}

void Organizer::delEvent(int d, int m, int y, int t_h, int t_m)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i]->getDay() == d && arr[i]->getMonth() == m && arr[i]->getYear() == y && arr[i]->getHour() == t_h && arr[i]->getMinute() == t_m)
		{
			arr.erase(arr.begin() + i);
			return;
		}
	}
}

void Organizer::sortEvent_by_date_and_time()
{
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 1; j < arr.size(); j++)
		{
			if (arr[j]->getYear() > arr[j - 1]->getYear())
			{
				swap(arr[j], arr[j - 1]);
			}
			else if (arr[j]->getYear() == arr[j - 1]->getYear())
			{
				if (arr[j]->getMonth() > arr[j - 1]->getMonth())
				{
					swap(arr[j], arr[j - 1]);

				}
				else if (arr[j]->getMonth() == arr[j - 1]->getMonth())
				{
					if (arr[j]->getDay() > arr[j - 1]->getDay())
							swap(arr[j], arr[j - 1]);
					else if (arr[j]->getDay() == arr[j - 1]->getDay())
					{
						if (arr[j]->getHour() > arr[j - 1]->getHour())
							swap(arr[j], arr[j - 1]);
					}
				}
			}
		}
	}
}

void Organizer::sortEvent_by_importance()
{
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 1; j < arr.size(); j++)
		{
			if (arr[j]->str_to_importance(arr[j]->getImportance()) > arr[j - 1]->str_to_importance(arr[j - 1]->getImportance()))
				swap(arr[j], arr[j - 1]);
		}
	}
}

void Organizer::searchEvent_by_importance(const string& i)
{
	Event::Importance im = Event::str_to_importance(i);
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i]->str_to_importance(arr[i]->getImportance()) == im)
			arr[i]->print();
	}
}

void Organizer::searchEvent_by_date(int d, int m, int y)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i]->getDay() == d && arr[i]->getMonth() == m && arr[i]->getYear() == y)
			arr[i]->print();
	}
}

void Organizer::save_organizer_txt(const string& file_name)
{
	if (file_name.rfind(".txt") == -1)
	{
		cout << "Invalid file extension" << endl;
		return;
	}
	fstream fs(file_name, ios::out);
	if (fs.is_open())
	{
		fs << name_owner << endl;
		for (int i = 0; i < arr.size(); i++)
		{
			if (shared_ptr<Birthday> b = dynamic_pointer_cast<Birthday>(arr[i]))
			{
				fs << "Birthday" << endl;
				fs << *b;
			}
			else if (shared_ptr<BusinessMeeting> bm = dynamic_pointer_cast<BusinessMeeting>(arr[i]))
			{
				fs << "Business meeting" << endl;
				fs << *bm;
			}
			else if (shared_ptr<PersonalMeeting> p = dynamic_pointer_cast<PersonalMeeting>(arr[i]))
			{
				fs << "Personal meeting" << endl;
				fs << *p;
			}
			else if (shared_ptr<VisitToSpecialist> v = dynamic_pointer_cast<VisitToSpecialist>(arr[i]))
			{
				fs << "Visit to specialist" << endl;
				fs << *v;
			}
			if (i == arr.size() - 1)
				break;
			fs << endl;
		}
		cout << "Save successful!" << endl;
		fs.close();
	}
}

void Organizer::load_organizer_txt(const string& file_name)
{
	if (file_name.rfind(".txt") == -1)
	{
		cout << "Invalid file extension" << endl;
		return;
	}
	fstream fs(file_name, ios::in);
	string buf;
	if (fs.is_open())
	{
		getline(fs, buf);
		name_owner = buf;
		while (!fs.eof())
		{
			getline(fs, buf);
			if (buf == "Birthday")
			{
				Birthday tmp;
				fs >> tmp;
				addEvent(tmp);
			}
			else if (buf == "Business meeting")
			{
				BusinessMeeting tmp;
				fs >> tmp;
				addEvent(tmp);
			}
			else if (buf == "Personal meeting")
			{
				PersonalMeeting tmp;
				fs >> tmp;
				addEvent(tmp);
			}
			else if (buf == "Visit to specialist")
			{
				VisitToSpecialist tmp;
				fs >> tmp;
				addEvent(tmp);
			}
		}
		cout << "Load successful!" << endl;
		fs.close();
	}
}

void Organizer::file_rename_txt(const char* old_name, const char* new_name)
{
	if (strstr(new_name, ".txt") == NULL || strstr(old_name, ".txt") == NULL)
	{
		cout << "Invalid file extension" << endl;
		return;
	}
	if (rename(old_name, new_name) == 0)
		cout << "Rename successful!" << endl;
	else
		cout << "Error" << endl;
}

void Organizer::file_remove_txt(const char* file_name)
{
	if (strstr(file_name, ".txt") == NULL)
	{
		cout << "Invalid file extension" << endl;
		return;
	}
	if (remove(file_name) == 0)
		cout << "Remove successful!" << endl;
	else
		cout << "Error!\n Couldn't remove file. Check filename." << endl;
}

void Organizer::print() const
{
	cout << setw(55) << name_owner << "'s organizer" << endl;
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i]->print();
	}
}

void Organizer::printToday() const
{
	time_t t = time(0);
	int d = localtime(&t)->tm_mday;
	int m = localtime(&t)->tm_mon + 1;
	int y = localtime(&t)->tm_year + 1900;
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i]->getDay() == d && arr[i]->getMonth() == m && arr[i]->getYear())
			arr[i]->print();
	}
}

void Organizer::printBirthday() const
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (shared_ptr<Birthday> b = dynamic_pointer_cast<Birthday>(arr[i]))
			b->print();
	}
}

void Organizer::printBusinessMeeting() const
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (shared_ptr<BusinessMeeting> bm = dynamic_pointer_cast<BusinessMeeting>(arr[i]))
			bm->print();
	}
}

void Organizer::printPersonalMeeting() const
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (shared_ptr<PersonalMeeting> p = dynamic_pointer_cast<PersonalMeeting>(arr[i]))
			p->print();
	}
}

void Organizer::printVisitToSpecialist() const
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (shared_ptr<VisitToSpecialist> v = dynamic_pointer_cast<VisitToSpecialist>(arr[i]))
			v->print();
	}
}

void Organizer::menu()
{
	string buf;
	cout << setw(55) << name_owner << "'s organizer" << endl;
	cout << "What you want to do?" << endl;
	do
	{
		cout << "add - to add new event\t\tprint - to print any events\tdelete - to remove event by day, month, year and time\n"
		    << "search - to search any events\tsort - to sort any events\tfile - to work with files\nexit - to finish" << endl;
		cout << "->";
		cin >> buf;
		if (buf == "add")
		{
			cout << "--------------------------------------------------------ADDITION--------------------------------------------------------" << endl;
			do
			{
				cout << "birthday - to add birthday\t\tbusiness - to add business meeting\t\tfinish - to finish the addition\n"
					<<"personal - to add personal meeting\tspecialist - to add visit to specialist" << endl;
				cout << "add->";
				cin >> buf;
				if (buf == "birthday")
				{
					try
					{ 
						Birthday obj;
						obj.input();
						addEvent(obj);
					}
					catch (const invalid_argument& ex)
					{
						cerr << "Error in class Birthday. " << ex.what() << endl;
					}
				}
				if (buf == "business")
				{
					try
					{
						BusinessMeeting obj;
						obj.input();
						addEvent(obj);
					}
					catch (const invalid_argument& ex)
					{
						cerr << "Error in class Business. " << ex.what() << endl;
					}
				}
				if (buf == "personal")
				{
					try
					{
						PersonalMeeting obj;
						obj.input();
						addEvent(obj);
					}
					catch (const invalid_argument& ex)
					{
						cerr << "Error in class PersonalMeeting. " << ex.what() << endl;
					}
				}
				if (buf == "specialist")
				{
					try
					{
						VisitToSpecialist obj;
						obj.input();
						addEvent(obj);
					}
					catch (const invalid_argument& ex)
					{
						cerr << "Error in class VisitToSpecialist. " << ex.what() << endl;
					}
				}
			} while (buf != "finish");
			cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		if (buf == "print")
		{
			cout << "---------------------------------------------------------PRINT----------------------------------------------------------" << endl;
			do
			{
				cout << "all - to print all events\t\tbirthday - to print birthdays\t\tbusiness - to print business meetings\n"
					<< "personal - to print personal meetings\tfinish - to finish print\t\ttoday - to print all today's events\n"
					<< "specialist - to print visits to specialist" << endl;
				cout << "print->";
				cin >> buf;
				if (buf == "all")
					print();
				if (buf == "birthday")
					printBirthday();
				if (buf == "business")
					printBusinessMeeting();
				if (buf == "personal")
					printPersonalMeeting();
				if (buf == "specialist")
					printVisitToSpecialist();
				if (buf == "today")
					printToday();

			} while (buf != "finish");
			cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		if (buf == "delete")
		{
			char buf1[500];
			int d, m, y, t_h, t_m;
			cout << "Enter date and time to delete the event:" << endl;
			cout << "day->";
			cin >> d;
			cout << "month->";
			cin >> m;
			cout << "year->";
			cin >> y;
			cout << "time (for example 12:00, 16:09, 9:21)->";
			cin >> buf1;
			t_h = stoi(strtok(buf1, ":,."));
			t_m = stoi(strtok(NULL, ""));
			delEvent(d, m, y, t_h, t_m);
		}
		if (buf == "search")
		{
			cout << "---------------------------------------------------------SEARCH---------------------------------------------------------" << endl;
			do
			{
				cout << "importance - to search events by importance\tdate - to search events by date\t\tfinish - to finish searching" << endl;
				cout << "search->";
				cin >> buf;
				if (buf == "importance")
				{
					cout << "Enter importance->";
					cin >> buf;
					searchEvent_by_importance(buf);
				}
				if (buf == "date")
				{
					int d, m, y;
					cout << "Enter date:" << endl;
					cout << "day->";
					cin >> d;
					cout << "month->";
					cin >> m;
					cout << "year->";
					cin >> y;
					searchEvent_by_date(d, m, y);
				}
			} while (buf != "finish");
			cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		if (buf == "sort")
		{
			cout << "----------------------------------------------------------SORT----------------------------------------------------------" << endl;
			do
			{
				cout << "importance - to sort events by importance\tdate - to sort events by date and time\nfinish - to finish sorting" << endl;
				cout << "sort->";
				cin >> buf;
				if (buf == "importance")
					sortEvent_by_importance();
				if (buf == "date")
					sortEvent_by_date_and_time();
			} while (buf != "finish");
			cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		if (buf == "file")
		{
			cout << "-----------------------------------------------------WORK WITH FILE-----------------------------------------------------" << endl;
			do
			{
				cout << "save - to save data in file\t\tload - to load data from file\t\trename - to rename file\nremove - to remove file\t\t\t" <<
					"finish - to finish work with files" << endl;
				cout << "file->";
				cin >> buf;
				if (buf == "save")
				{
					cout << "Enter desired file name(with extension .txt)->";
					cin >> buf;
					save_organizer_txt(buf);
				}
				if (buf == "load")
				{
					cout << "Enter desired file name(with extension .txt)->";
					cin >> buf;
					load_organizer_txt(buf);
				}
				if (buf == "rename")
				{
					char buf1[500], buf2[500];
					cout << "Enter file name you want to change(with extension .txt)->";
					cin >> buf1;
					cout << "Enter new desired file name(with extension .txt)->";
					cin >> buf2;
					file_rename_txt(buf1, buf2);
				}
				if (buf == "remove")
				{
					char buf1[500];
					cout << "Enter file name you want to remove(with extension .txt)->";
					cin >> buf1;
					file_remove_txt(buf1);
				}
			} while (buf != "finish");
			cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	} while (buf != "exit");
}
