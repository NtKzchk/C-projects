#include"readers.h"

//function that get index reader by id
int get_Reader_index(Reader* arr, int size, int id)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].id == id)
			return i;
	}
	return -1;
}
//function that enters data about the readers
void input_Reader(Reader& obj)
{
	char buf[100];
	cout << "Last name->";
	cin.getline(buf, 100);
	obj.l_name = new char[strlen(buf) + 1];
	strcpy(obj.l_name, buf);
	cout << "First name->";
	cin.getline(buf, 100);
	obj.f_name = new char[strlen(buf) + 1];
	strcpy(obj.f_name, buf);
	cout << "Middle name->";
	cin.getline(buf, 100);
	obj.m_name = new char[strlen(buf) + 1];
	strcpy(obj.m_name, buf);
	cout << "Enter the birthday:" << endl;
	cout << "day->";
	cin >> obj.day;
	cin.ignore();
	cout << "mounth->";
	cin.getline(buf, 100);
	obj.month = new char[strlen(buf) + 1];
	strcpy(obj.month, buf);
	cout << "year->";
	cin >> obj.year;
	cin.ignore();
	cout << "Passport id->";
	cin >> obj.passport_id;
	cin.ignore();
}
//function that add the reader
void add_Reader(Reader*& arr, int& size, int& id)
{
	if (size == 0)
		arr = new Reader[1];
	else
	{
		Reader* tmp = new Reader[size + 1];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = arr[i];
		}
		delete[]arr;
		arr = tmp;
	}
	arr[size].id = id++;
	input_Reader(arr[size]);
	size++;
}
//function that delete the reader by id
void del_Reader_by_id(Reader*& arr, int& size, int del_id)
{
	if (get_Reader_index(arr, size, del_id) == -1)
		return;
	int j = get_Reader_index(arr, size, del_id);
	for (int i = 0; i < sizeof(arr[j].list_book) / sizeof(arr[j].list_book[0]); i++)
	{
		if (arr[j].list_book[i] != 0)
		{
			cout << "This reader has a book. Recording about him cannot be deleted." << endl;
			return;
		}
	}
	Reader* tmp = new Reader[size - 1];
	for (int i = 0, k = 0; i < size; i++)
	{
		if (i == j)
			continue;
		tmp[k++] = arr[i];
	}
	delete[]arr[j].f_name;
	delete[]arr[j].l_name;
	delete[]arr[j].m_name;
	delete[]arr[j].month;
	delete[]arr;
	arr = tmp;
	size--;
}
//function for full editing data about reader
void full_Reader_edit(Reader*& arr, int size, int id)
{
	char buf[100];
	int i = get_Reader_index(arr, size, id);
	cout << "!!!!!!!!!!!!!!!!!!!!! Full editing of reader data !!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "New last name (was " << arr[i].l_name << ")->";
	delete[]arr[i].l_name;
	cin.getline(buf, 100);
	arr[i].l_name = new char[strlen(buf) + 1];
	strcpy(arr[i].l_name, buf);
	cout << "New first name (was " << arr[i].f_name << ")->";
	delete[]arr[i].f_name;
	cin.getline(buf, 100);
	arr[i].f_name = new char[strlen(buf) + 1];
	strcpy(arr[i].f_name, buf);
	cout << "New middle name (was " << arr[i].m_name << ")->";
	delete[]arr[i].m_name;
	cin.getline(buf, 100);
	arr[i].m_name = new char[strlen(buf) + 1];
	strcpy(arr[i].m_name, buf);
	cout << "Enter new birthday:";
	cout << "day->";
	cin >> arr[i].day;
	cin.ignore();
	cout << "mounth->";
	delete[]arr[i].month;
	cin.getline(buf, 100);
	arr[i].month = new char[strlen(buf) + 1];
	strcpy(arr[i].month, buf);
	cout << "year->";
	cin >> arr[i].year;
	cin.ignore();
	cout << "Passport id->";
	cin >> arr[i].passport_id;
	cin.ignore();
}
//function for partial editing data about reader
void part_Reader_edit(Reader*& arr, int size, int id)
{
	char buf[50];
	int i = get_Reader_index(arr, size, id), op;
	cout << "!!!!!!!!!!!!!!!!!!!!! Partial editing of reader data !!!!!!!!!!!!!!!!!!!!!" << endl;
	do
	{
		cout << "What you want to change?" << endl;
		cout << "1 - to change last name\t\t\t2 - to change first name\t\t3 - to change middle name\n4 - to change birthday\t\t\t5 - to change passport id\t\t6 - to finish editing" << endl;
		cout << "->";
		cin >> op;
		cin.ignore();
		switch (op)
		{
		case 1:
			cout << "New last name (was " << arr[i].l_name << ")->";
			delete[]arr[i].l_name;
			cin.getline(buf, 100);
			arr[i].l_name = new char[strlen(buf) + 1];
			strcpy(arr[i].l_name, buf);
			break;
		case 2:
			cout << "New first name (was " << arr[i].f_name << ")->";
			delete[]arr[i].f_name;
			cin.getline(buf, 100);
			arr[i].f_name = new char[strlen(buf) + 1];
			strcpy(arr[i].f_name, buf);
			break;
		case 3:
			cout << "New middle name (was " << arr[i].m_name << ")->";
			delete[]arr[i].m_name;
			cin.getline(buf, 100);
			arr[i].m_name = new char[strlen(buf) + 1];
			strcpy(arr[i].m_name, buf);
			break;
		case 4:
			cout << "Enter new birthday (was " << arr[i].day << " " << arr[i].month << " " << arr[i].year << "):" << endl;
			cout << "day->";
			cin >> arr[i].day;
			cin.ignore();
			cout << "mounth->";
			delete[]arr[i].month;
			cin.getline(buf, 100);
			arr[i].month = new char[strlen(buf) + 1];
			strcpy(arr[i].month, buf);
			cout << "year->";
			cin >> arr[i].year;
			cin.ignore();
			break;
		case 5:
			cout << "Passport id->";
			cin >> arr[i].passport_id;
			cin.ignore();
			break;
		}
	} while (op != 6);
}
//function that search readers by full name
int search_Reader_by_full_name(Reader* r_arr, int r_size)
{
	char search_l_name[50];
	char search_f_name[50];
	char search_m_name[50];
	cout << "Enter the last name for search->";
	cin.getline(search_l_name, 50);
	cout << "Enter the first name for search->";
	cin.getline(search_f_name, 50);
	cout << "Enter the middle name for search->";
	cin.getline(search_m_name, 50);
	for (int i = 0; i < r_size; i++)
	{
		if (strcmp(r_arr[i].l_name, search_l_name) == 0 && strcmp(r_arr[i].f_name, search_f_name) == 0 && strcmp(r_arr[i].m_name, search_m_name) == 0)
			return i;
	}
}
//function that search readers by id
int search_Reader_by_id(Reader* r_arr, int r_size)
{
	int search_el;
	cout << "Enter the reader id to search->";
	cin >> search_el;
	cin.ignore();
	for (int i = 0; i < r_size; i++)
	{
		if (r_arr[i].id == search_el)
			return i;
	}
}
//function that search readers by number of passport
int search_Reader_by_passport(Reader* r_arr, int r_size)
{
	int search_el;
	cout << "Enter the passport id to search->";
	cin >> search_el;
	cin.ignore();
	for (int i = 0; i < r_size; i++)
	{
		if (r_arr[i].passport_id == search_el)
			return i;
	}
}