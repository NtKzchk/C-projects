#include"books.h"

//translation of  char array value into genre
Genre str_to_genre(const char* str)
{
	if (strcmp(str, "Fantasy") == 0)
		return Fantasy;
	else if (strcmp(str, "Sci_Fi") == 0)
		return Sci_Fi;
	else if (strcmp(str, "Mystery") == 0)
		return Mystery;
	else if (strcmp(str, "Romance") == 0)
		return Romance;
	else if (strcmp(str, "Horror") == 0)
		return Horror;
	else if (strcmp(str, "History") == 0)
		return History;
	else if (strcmp(str, "Health") == 0)
		return Health;
	else if (strcmp(str, "Humor") == 0)
		return Humor;
	else
		return Unknown;
}
//translation of genre value into char array
const char* genre_to_str(Genre s)
{
	switch (s)
	{
	case Fantasy:
		return "Fantasy";
	case Sci_Fi:
		return "Sci_Fi";
	case Mystery:
		return "Mystery";
	case Romance:
		return "Romance";
	case Horror:
		return "Horror";
	case History:
		return "History";
	case Health:
		return "Health";
	case Humor:
		return "Humor";
	}
	return "Unknown";
}
//function that get index book by id
int get_Book_index(Book* arr, int size, int id)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].id == id)
			return i;
	}
	return -1;
}
//function that enters data about the book
void input_Book(Book& obj)
{
	char buf[100];
	cout << "Enter the date of publication:" << endl;
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
	cout << "Name of the book->";
	cin.getline(buf, 100);
	obj.name = new char[strlen(buf) + 1];
	strcpy(obj.name, buf);
	cout << "Author name->";
	cin.getline(buf, 100);
	obj.author_name = new char[strlen(buf) + 1];
	strcpy(obj.author_name, buf);
	Genre g[]{ Fantasy, Sci_Fi, Mystery, Romance, Horror, History, Health, Humor, Unknown };
	cout << "Possible genres:" << endl;
	for (int i = 0; i < size(g); i++)
	{
		cout << "-" << genre_to_str(g[i]) << endl;
	}
	cout << "Genre->";
	cin.getline(buf, 100);
	obj.genre = str_to_genre(buf);
	cout << "Book cost->";
	cin >> obj.cost;
	cin.ignore();
	cout << "Rating->";
	cin >> obj.rating;
	cin.ignore();
}
//function that add the book
void add_Book(Book*& arr, int& size, int& id)
{
	if (size == 0)
		arr = new Book[1];
	else
	{
		Book* tmp = new Book[size + 1];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = arr[i];
		}
		delete[]arr;
		arr = tmp;
	}
	arr[size].id = id++;
	input_Book(arr[size]);
	size++;
}
//function that delete the book by id
void del_Book_by_id(Book*& arr, int& size, int del_id)
{
	if (get_Book_index(arr, size, del_id) == -1)
		return;
	int j = get_Book_index(arr, size, del_id);
	if (arr[j].id_reader != 0)
	{
		cout << "This book is in the possession of the reader. It can not be removed." << endl;
		return;
	}
	Book* tmp = new Book[size - 1];
	for (int i = 0, k = 0; i < size; i++)
	{
		if (j == i)
			continue;
		tmp[k++] = arr[i];
	}
	delete[]arr[j].month;
	delete[]arr[j].name;
	delete[]arr[j].author_name;
	delete[]arr;
	arr = tmp;
	size--;
}
//function for full editing data about book
void full_Book_edit(Book*& arr, int size, int id)
{
	char buf[100];
	int i = get_Book_index(arr, size, id);
	cout << "!!!!!!!!!!!!!!!!!!!!! Full editing of book data !!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "Enter new date of publication (was " << arr[i].day << " " << arr[i].month << " " << arr[i].year << "):" << endl;
	delete[]arr[i].month;
	cout << "day->";
	cin >> arr[i].day;
	cin.ignore();
	cout << "month->";
	cin.getline(buf, 100);
	arr[i].month = new char[strlen(buf) + 1];
	strcpy(arr[i].month, buf);
	cout << "year->";
	cin >> arr[i].year;
	cout << "New name of the book (was " << arr[i].name << ")->";
	delete[]arr[i].name;
	cin.getline(buf, 100);
	arr[i].name = new char[strlen(buf) + 1];
	strcpy(arr[i].name, buf);
	cout << "New author name (was " << arr[i].author_name << ")->";
	delete[]arr[i].author_name;
	cin.getline(buf, 100);
	arr[i].author_name = new char[strlen(buf) + 1];
	strcpy(arr[i].author_name, buf);
	cout << "New genre (was " << arr[i].genre << ")->";
	cin.getline(buf, 100);
	arr[i].genre = str_to_genre(buf);
	cout << "New book cost (was " << arr[i].cost << ")->";
	cin >> arr[i].cost;
	cin.ignore();
	cout << "New rating (was " << arr[i].rating << ")->";
	cin >> arr[i].rating;
	cin.ignore();
}
//function for partial editing data about book
void part_Book_edit(Book*& arr, int size, int id)
{
	char buf[50];
	int i = get_Book_index(arr, size, id), op;
	cout << "!!!!!!!!!!!!!!!!!!!!! Partial editing of book data !!!!!!!!!!!!!!!!!!!!!" << endl;
	do
	{
		cout << "What you want to change?" << endl;
		cout << "1 - to change date of publication\t2 - to change name of the book\t\t3 - to change author name\n4 - to change genre\t\t\t5 - to change book cost";
		cout << "\t\t\t6 - to change rating\n7 - to finish editing" << endl;
		cout << "->";
		cin >> op;
		cin.ignore();
		switch (op)
		{
		case 1:
			cout << "Enter new date of publication (was " << arr[i].day << " " << arr[i].month << " " << arr[i].year << "):" << endl;
			delete[]arr[i].month;
			cout << "day->";
			cin >> arr[i].day;
			cin.ignore();
			cout << "month->";
			cin.getline(buf, 100);
			arr[i].month = new char[strlen(buf) + 1];
			strcpy(arr[i].month, buf);
			cout << "year->";
			cin >> arr[i].year;
			break;
		case 2:
			cout << "New name of the book (was " << arr[i].name << ")->";
			delete[]arr[i].name;
			cin.getline(buf, 100);
			arr[i].name = new char[strlen(buf) + 1];
			strcpy(arr[i].name, buf);
			break;
		case 3:
			cout << "New author name (was " << arr[i].author_name << ")->";
			delete[]arr[i].author_name;
			cin.getline(buf, 100);
			arr[i].author_name = new char[strlen(buf) + 1];
			strcpy(arr[i].author_name, buf);
			break;
		case 4:
			cout << "New genre (was " << arr[i].genre << ")->";
			cin.getline(buf, 100);
			arr[i].genre = str_to_genre(buf);
			break;
		case 5:
			cout << "New book cost (was " << arr[i].cost << ")->";
			cin >> arr[i].cost;
			cin.ignore();
			break;
		case 6:
			cout << "New rating (was " << arr[i].rating << ")->";
			cin >> arr[i].rating;
			cin.ignore();
			break;
		}
	} while (op != 7);
}