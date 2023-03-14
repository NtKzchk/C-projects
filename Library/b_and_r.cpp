#include"b_and_r.h"

//function printing books
void print_Book(Book obj, Reader* arr, int size)
{
	cout << "############################## Book ##############################" << endl;
	cout << "Book ID: " << obj.id << endl;
	cout << "The date of publication: " << obj.day << " " << obj.month << " " << obj.year << endl;
	cout << "Name of the book: " << obj.name << endl;
	cout << "Author name: " << obj.author_name << endl;
	cout << "Genre: " << genre_to_str(obj.genre) << endl;
	cout << "Book cost: " << obj.cost << "$" << endl;
	cout << "Rating: " << obj.rating << endl;
	if (obj.id_reader != 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (arr[i].id == obj.id_reader)
				cout << "Full name of the reader who has the book: " << arr[i].l_name << " " << arr[i].f_name << " " << arr[i].m_name << endl;
		}
	}
	if (obj.popular > 0)
		cout << "Popular: " << obj.popular << endl;
	cout << "##################################################################" << endl;
}
//function printing readers
void print_Reader(Reader obj, Book* arr, int size)
{
	cout << "######################### Reader #########################" << endl;
	cout << "Reader ID: " << obj.id << endl;
	cout << "Full name: " << obj.l_name << " " << obj.f_name << " " << obj.m_name << endl;
	cout << "Birthday: " << obj.day << " " << obj.month << " " << obj.year << endl;
	cout << "Passport id: " << obj.passport_id << endl;
	cout << "Number of books read: " << obj.num_book_read << endl;
	cout << "Books that the reader have: " << endl;
	for (int i = 0; i < sizeof(obj.list_book) / sizeof(obj.list_book[0]); i++)
	{
		if (obj.list_book[i] != 0)
		{

			cout << arr[get_Book_index(arr, size, obj.list_book[i])].name << " (ID = " << obj.list_book[i] << ")" << endl;
		}
	}
	cout << "##########################################################" << endl;
}
//function giving a book
void give_book(Book*& b_arr, Reader*& r_arr, int b_size, int r_size)
{
	int b_id, r_id;
	cout << "\n\nId reader who wants to take the book->";
	cin >> r_id;
	cin.ignore();
	cout << "What book reader wants (id of the book)->";
	cin >> b_id;
	cin.ignore();
	int book_ind = get_Book_index(b_arr, b_size, b_id), reader_ind = get_Reader_index(r_arr, r_size, r_id);
	if (book_ind == -1 || reader_ind == -1)
		return;
	if (r_arr[reader_ind].num_book_read == size(r_arr[reader_ind].list_book))
		cout << "This reader can not take the book (limit of 5 books).\nERROR!ERROR!ERROR!ERROR!ERROR!ERROR!ERROR!ERROR!ERROR!ERROR\n" << endl;
	else if (b_arr[book_ind].id_reader != 0)
		cout << "This book is not in the library.\nERROR!ERROR!ERROR!ERROR!ERROR!!!\n" << endl;
	else
	{
		b_arr[book_ind].id_reader = r_id;
		b_arr[book_ind].time_took_book = time(NULL);
		b_arr[book_ind].popular++;
		for (int j = 0; j < size(r_arr[reader_ind].list_book); j++)
		{
			if (r_arr[reader_ind].list_book[j] == 0)
			{
				r_arr[reader_ind].list_book[j] = b_id;
				r_arr[reader_ind].num_book_read++;
				cout << "Operation successful!\n\n" << endl;
				break;
			}
		}
	}
}
//function return a book
void return_book(Book*& b_arr, Reader*& r_arr, int b_size, int r_size)
{
	int b_id, r_id;
	cout << "\n\nId reader who wants to return the book->";
	cin >> r_id;
	cin.ignore();
	cout << "What book reader wants to return (id of the book)->";
	cin >> b_id;
	cin.ignore();
	int book_ind = get_Book_index(b_arr, b_size, b_id), reader_ind = get_Reader_index(r_arr, r_size, r_id);
	if (book_ind == -1 || reader_ind == -1)
		return;
	long allowed_time = 604800, over_days = 0, c = 0; //it is allowed to keep the book for no more than 7 days (7 days = 604800 seconds)
	for (int i = 0; i < size(r_arr[i].list_book); i++)
	{
		if (r_arr[reader_ind].list_book[i] == b_id)
		{
			r_arr[reader_ind].list_book[i] = 0;
			b_arr[book_ind].id_reader = 0;
			b_arr[book_ind].time_took_book = time(NULL) - b_arr[book_ind].time_took_book;
			if (b_arr[book_ind].time_took_book - 86400 > allowed_time)
			{
				over_days = (b_arr[book_ind].time_took_book - allowed_time);
				cout << "Overdue " << over_days / 86400 << " days. Forfeit: " << over_days * 10 << " penalties." << endl;
			}
			cout << "Operation successful!\n\n" << endl;
			b_arr[book_ind].time_took_book = 0;
			c++;
		}
	}
	if (c == 0)
		cout << "This reader does not have such a book.\nERROR!ERROR!ERROR!ERROR!ERROR!ERROR!!!\n" << endl;
}

//function that search the books by author
void search_Book_by_author(Book* b_arr, int b_size, Reader* r_arr, int r_size)
{
	char search_el[50];
	cout << "By which author to search?";
	cout << "author->";
	cin.getline(search_el, 50);
	for (int i = 0; i < b_size; i++)
	{
		if (strcmp(b_arr[i].author_name, search_el) == 0)
			print_Book(b_arr[i], r_arr, r_size);
	}
}
//function that search the books by title
void search_Book_by_title(Book* b_arr, int b_size, Reader* r_arr, int r_size)
{
	char search_el[50];
	cout << "What book title to search?";
	cout << "title->";
	cin.getline(search_el, 50);
	for (int i = 0; i < b_size; i++)
	{
		if (strcmp(b_arr[i].name, search_el) == 0)
			print_Book(b_arr[i], r_arr, r_size);
	}
}
//function that search the books by genre
void search_Book_by_genre(Book* b_arr, int b_size, Reader* r_arr, int r_size)
{
	Genre g[]{ Fantasy, Sci_Fi, Mystery, Romance, Horror, History, Health, Humor, Unknown };
	cout << "Possible genres:" << endl;
	for (int i = 0; i < size(g); i++)
	{
		cout << "-" << genre_to_str(g[i]) << endl;
	}
	char search_el[50];
	cout << "What genre books to search:";
	cout << "genre->";
	cin.getline(search_el, 500);
	for (int i = 0; i < b_size; i++)
	{
		if (strcmp(genre_to_str(b_arr[i].genre), search_el) == 0)
			print_Book(b_arr[i], r_arr, r_size);
	}
}
//function that search the books by popular
void search_Book_by_popular(Book* b_arr, int b_size, Reader* r_arr, int r_size)
{
	int search_el;
	cout << "Enter the popular of books to search->";
	cin >> search_el;
	cin.ignore();
	for (int i = 0; i < b_size; i++)
	{
		if (b_arr[i].popular == search_el)
			print_Book(b_arr[i], r_arr, r_size);
	}
}
//function that search the readers by the number of books read
void search_Reader_by_num_book_read(Reader* r_arr, int r_size, Book* b_arr, int b_size)
{
	int search_el;
	cout << "Enter the number of books read to search->";
	cin >> search_el;
	cin.ignore();
	for (int i = 0; i < r_size; i++)
	{
		if (r_arr[i].num_book_read == search_el)
			print_Reader(r_arr[i], b_arr, b_size);
	}
}

//function that shows the books the reader has
void print_book_readers_read(Book* b_arr, int b_size, Reader* r_arr, int r_size)
{
	cout << "-------------------------Books that the readers has------------------------" << endl;
	for (int i = 0; i < b_size; i++)
	{
		if (b_arr[i].id_reader != 0)
			print_Book(b_arr[i], r_arr, r_size);
	}
	cout << "---------------------------------------------------------------------------" << endl;
}
//function that print the most active reader
void print_most_active_reader(Reader* r_arr, int r_size, Book* b_arr, int b_size)
{
	for (int i = 0; i < r_size; i++)
	{
		for (int j = r_size - 1; j > i; j--)
		{
			if (r_arr[j].num_book_read > r_arr[j - 1].num_book_read)
			{
				swap(r_arr[j], r_arr[j - 1]);
			}
		}
	}
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!! The most active readers !!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	for (int i = 0; i < r_size; i++)
	{
		print_Reader(r_arr[i], b_arr, b_size);
	}
}
//function that print the most popular books in some genre
void print_most_popular_book_in_genre(Book* b_arr, int b_size, Reader* r_arr, int r_size)
{
	char buf[50];
	Genre g[]{ Fantasy, Sci_Fi, Mystery, Romance, Horror, History, Health, Humor, Unknown };
	cout << "In what genre you want to search:" << endl;
	for (int i = 0; i < size(g); i++)
	{
		cout << "-" << genre_to_str(g[i]) << endl;
	}
	cout << "Genre->";
	cin.getline(buf, 50);
	int t_size = 0;
	for (int i = 0, j = 0; i < b_size; i++)
	{
		if (strcmp(buf, genre_to_str(b_arr[i].genre)) == 0)
		{
			t_size++;
		}
	}
	if (t_size == 0)
		cout << "In the library there are no books with this genre." << endl;
	else
	{
		Book* tmp = new Book[t_size];
		for (int i = 0, j = 0; i < b_size; i++)
		{
			if (strcmp(buf, genre_to_str(b_arr[i].genre)) == 0)
			{
				tmp[j++] = b_arr[i];
			}
		}
		for (int i = 0; i < t_size; i++)
		{
			for (int j = t_size - 1; j > i; j--)
			{
				if (tmp[j].popular > tmp[j - 1].popular)
				{
					swap(tmp[j], tmp[j - 1]);
				}
			}
		}
		for (int i = 0; i < t_size; i++)
		{
			print_Book(tmp[i], r_arr, r_size);
		}
		delete[]tmp;
	}
}
//function that print readers that have expired return time
void print_reader_that_have_expired_return_data(Book* b_arr, int b_size, Reader* r_arr, int r_size)
{
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||| Debtors |||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	long allowed_time = 604800;
	for (int i = 0; i < b_size; i++)
	{
		int over_days = b_arr[i].time_took_book - allowed_time;
		if (b_arr[i].time_took_book - 86400 > allowed_time)
		{
			print_Reader(r_arr[get_Reader_index(r_arr, r_size, b_arr[i].id_reader)], b_arr, b_size);
			cout << "Overdue " << over_days / 86400 << " days. Forfeit: " << over_days * 10 << " penalties." << endl;
		}
	}
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
}

//function that sort the reader by the number of books read
void sort_Reader_by_num_book_read(Reader*& r_arr, int r_size, Book* b_arr, int b_size)
{
	for (int i = 0; i < r_size; i++)
	{
		for (int j = r_size - 1; j > i; j--)
		{
			if (r_arr[j].num_book_read > r_arr[j - 1].num_book_read)
			{
				swap(r_arr[j], r_arr[j - 1]);
			}
		}
	}
	for (int i = 0; i < r_size; i++)
	{
		print_Reader(r_arr[i], b_arr, b_size);
	}
}
//function that search readers by id
void sort_Reader_by_ID(Reader*& r_arr, int r_size, Book* b_arr, int b_size)
{
	for (int i = 0; i < r_size; i++)
	{
		for (int j = r_size - 1; j > i; j--)
		{
			if (r_arr[j].id < r_arr[j - 1].id)
			{
				swap(r_arr[j], r_arr[j - 1]);
			}
		}
	}
	for (int i = 0; i < r_size; i++)
	{
		print_Reader(r_arr[i], b_arr, b_size);
	}
}
//function that search readers by number of passport
void sort_Reader_by_passportID(Reader*& r_arr, int r_size, Book* b_arr, int b_size)
{
	for (int i = 0; i < r_size; i++)
	{
		for (int j = r_size - 1; j > i; j--)
		{
			if (r_arr[j].passport_id < r_arr[j - 1].passport_id)
			{
				swap(r_arr[j], r_arr[j - 1]);
			}
		}
	}
	for (int i = 0; i < r_size; i++)
	{
		print_Reader(r_arr[i], b_arr, b_size);
	}
}
//function that search readers by name
void sort_Reader_by_name(Reader*& r_arr, int r_size, Book* b_arr, int b_size)
{
	for (int i = 0; i < r_size; i++)
	{
		for (int j = r_size - 1; j > i; j--)
		{
			if (strcmp(r_arr[j].l_name, r_arr[j - 1].l_name) < 0)
			{
				if (strcmp(r_arr[j].l_name, r_arr[j - 1].l_name) == 0)
				{
					if (strcmp(r_arr[j].f_name, r_arr[j - 1].f_name) < 0)
					{
						if (strcmp(r_arr[j].f_name, r_arr[j - 1].f_name) == 0)
						{
							if (strcmp(r_arr[j].m_name, r_arr[j - 1].m_name) < 0)
							{
								swap(r_arr[j], r_arr[j - 1]);
							}
						}
						else
							swap(r_arr[j], r_arr[j - 1]);
					}
				}
				else
					swap(r_arr[j], r_arr[j - 1]);
			}
		}
	}
	for (int i = 0; i < r_size; i++)
	{
		print_Reader(r_arr[i], b_arr, b_size);
	}
}

//function that sort the book by author
void sort_Book_by_author(Book*& b_arr, int b_size, Reader* r_arr, int r_size)
{
	for (int i = 0; i < b_size; i++)
	{
		for (int j = b_size - 1; j > i; j--)
		{
			if (strcmp(b_arr[j].author_name, b_arr[j - 1].author_name) < 0)
			{
				swap(b_arr[j], b_arr[j - 1]);
			}
		}
	}
	for (int i = 0; i < b_size; i++)
	{
		print_Book(b_arr[i], r_arr, r_size);
	}
}
//function that sort the book by title
void sort_Book_by_name(Book*& b_arr, int b_size, Reader* r_arr, int r_size)
{
	for (int i = 0; i < b_size; i++)
	{
		for (int j = b_size - 1; j > i; j--)
		{
			if (strcmp(b_arr[j].name, b_arr[j - 1].name) < 0)
			{
				swap(b_arr[j], b_arr[j - 1]);
			}
		}
	}
	for (int i = 0; i < b_size; i++)
	{
		print_Book(b_arr[i], r_arr, r_size);
	}
}
//function that sort the book by genre
void sort_Book_by_genre(Book*& b_arr, int b_size, Reader* r_arr, int r_size)
{
	for (int i = 0; i < b_size; i++)
	{
		for (int j = b_size - 1; j > i; j--)
		{
			if (strcmp(genre_to_str(b_arr[j].genre), genre_to_str(b_arr[j - 1].genre)) < 0)
			{
				swap(b_arr[j], b_arr[j - 1]);
			}
		}
	}
	for (int i = 0; i < b_size; i++)
	{
		print_Book(b_arr[i], r_arr, r_size);
	}
}
//function that sort the book by popular
void sort_Book_by_popular(Book*& b_arr, int b_size, Reader* r_arr, int r_size)
{
	for (int i = 0; i < b_size; i++)
	{
		for (int j = b_size - 1; j > i; j--)
		{
			if (b_arr[j].popular > b_arr[j - 1].popular)
			{
				swap(b_arr[j], b_arr[j - 1]);
			}
		}
	}
	for (int i = 0; i < b_size; i++)
	{
		print_Book(b_arr[i], r_arr, r_size);
	}
}

//function to save data about books and readers
void Save(FILE*& f, Book* b_arr, int b_size, Reader* r_arr, int r_size)
{
	//function to save data about books
	fwrite(&b_size, sizeof(int), 1, f);
	for (int i = 0; i < b_size; i++)
	{
		fwrite(&b_arr[i].id, sizeof(int), 1, f);
		fwrite(&b_arr[i].day, sizeof(int), 1, f);
		int len1 = strlen(b_arr[i].month) + 1;
		fwrite(&len1, sizeof(int), 1, f);
		fwrite(b_arr[i].month, sizeof(char), len1, f);
		fwrite(&b_arr[i].year, sizeof(int), 1, f);
		int len2 = strlen(b_arr[i].name) + 1;
		fwrite(&len2, sizeof(int), 1, f);
		fwrite(b_arr[i].name, sizeof(char), len2, f);
		int len3 = strlen(b_arr[i].author_name) + 1;
		fwrite(&len3, sizeof(int), 1, f);
		fwrite(b_arr[i].author_name, sizeof(char), len3, f);
		fwrite(&b_arr[i].genre, sizeof(Genre), 1, f);
		fwrite(&b_arr[i].cost, sizeof(int), 1, f);
		fwrite(&b_arr[i].rating, sizeof(double), 1, f);
		fwrite(&b_arr[i].id_reader, sizeof(int), 1, f);
		fwrite(&b_arr[i].time_took_book, sizeof(time_t), 1, f);
		fwrite(&b_arr[i].popular, sizeof(int), 1, f);
	}
	//function to save data about readers
	fwrite(&r_size, sizeof(int), 1, f);
	for (int i = 0; i < r_size; i++)
	{
		fwrite(&r_arr[i].id, sizeof(int), 1, f);
		int len1 = strlen(r_arr[i].l_name) + 1;
		fwrite(&len1, sizeof(int), 1, f);
		fwrite(r_arr[i].l_name, sizeof(char), len1, f);
		int len2 = strlen(r_arr[i].f_name) + 1;
		fwrite(&len2, sizeof(int), 1, f);
		fwrite(r_arr[i].f_name, sizeof(char), len2, f);
		int len3 = strlen(r_arr[i].m_name) + 1;
		fwrite(&len3, sizeof(int), 1, f);
		fwrite(r_arr[i].m_name, sizeof(char), len3, f);
		fwrite(&r_arr[i].day, sizeof(int), 1, f);
		int len4 = strlen(r_arr[i].month) + 1;
		fwrite(&len4, sizeof(int), 1, f);
		fwrite(r_arr[i].month, sizeof(char), len4, f);
		fwrite(&r_arr[i].year, sizeof(int), 1, f);
		fwrite(&r_arr[i].passport_id, sizeof(int), 1, f);
		fwrite(&r_arr[i].num_book_read, sizeof(int), 1, f);
		for (int j = 0; j < 5; j++)
		{
			fwrite(&r_arr[i].list_book[j], sizeof(int), 1, f);
		}
		fwrite(&r_arr[i].num_book_read, sizeof(int), 1, f);
	}
}
//function to load data about books and readers
void Load(FILE* f, Book*& b_arr, int& b_size, int& b_id, Reader*& r_arr, int& r_size, int& r_id)
{
	//release space for load
	for (int i = 0; i < b_size; i++)
	{
		delete[]b_arr[i].name;
		delete[]b_arr[i].author_name;
		delete[]b_arr[i].month;
	}
	delete[]b_arr;
	//function to load data about books
	fread(&b_size, sizeof(int), 1, f);
	b_arr = new Book[b_size];
	for (int i = 0; i < b_size; i++)
	{
		b_id = fread(&b_arr[i].id, sizeof(int), 1, f) + 1;
		fread(&b_arr[i].day, sizeof(int), 1, f);
		int len1 = 0, len2 = 0, len3 = 0;
		fread(&len1, sizeof(int), 1, f);
		b_arr[i].month = new char[len1];
		fread(b_arr[i].month, sizeof(char), len1, f);
		fread(&b_arr[i].year, sizeof(int), 1, f);
		fread(&len2, sizeof(int), 1, f);
		b_arr[i].name = new char[len2];
		fread(b_arr[i].name, sizeof(char), len2, f);
		fread(&len3, sizeof(int), 1, f);
		b_arr[i].author_name = new char[len3];
		fread(b_arr[i].author_name, sizeof(char), len3, f);
		fread(&b_arr[i].genre, sizeof(Genre), 1, f);
		fread(&b_arr[i].cost, sizeof(int), 1, f);
		fread(&b_arr[i].rating, sizeof(double), 1, f);
		fread(&b_arr[i].id_reader, sizeof(int), 1, f);
		fread(&b_arr[i].time_took_book, sizeof(time_t), 1, f);
		fread(&b_arr[i].popular, sizeof(int), 1, f);
	}
	//release space for load
	for (int i = 0; i < r_size; i++)
	{
		delete[]r_arr[i].f_name;
		delete[]r_arr[i].m_name;
		delete[]r_arr[i].l_name;
		delete[]r_arr[i].month;
	}
	delete[]r_arr;
	//function to load data about readers
	fread(&r_size, sizeof(int), 1, f);
	r_arr = new Reader[r_size];
	for (int i = 0; i < r_size; i++)
	{
		fread(&r_arr[i].id, sizeof(int), 1, f);
		r_id = r_arr[i].id + 1;
		int len1 = 0, len2 = 0, len3 = 0, len4 = 0;
		fread(&len1, sizeof(int), 1, f);
		r_arr[i].l_name = new char[len1];
		fread(r_arr[i].l_name, sizeof(char), len1, f);
		fread(&len2, sizeof(int), 1, f);
		r_arr[i].f_name = new char[len2];
		fread(r_arr[i].f_name, sizeof(char), len2, f);
		fread(&len3, sizeof(int), 1, f);
		r_arr[i].m_name = new char[len3];
		fread(r_arr[i].m_name, sizeof(char), len3, f);
		fread(&r_arr[i].day, sizeof(int), 1, f);
		fread(&len4, sizeof(int), 1, f);
		r_arr[i].month = new char[len4];
		fread(r_arr[i].month, sizeof(char), len4, f);
		fread(&r_arr[i].year, sizeof(int), 1, f);
		fread(&r_arr[i].passport_id, sizeof(int), 1, f);
		fread(&r_arr[i].num_book_read, sizeof(int), 1, f);
		for (int j = 0; j < 5; j++)
		{
			fread(&r_arr[i].list_book[j], sizeof(int), 1, f);
		}
		fread(&r_arr[i].num_book_read, sizeof(int), 1, f);
	}
}
//menu function - call functions as required
void menu(Book*& b_arr, int& b_size, int& b_id, Reader*& r_arr, int& r_size, int& r_id)
{
	char buf[50];
	cout << setw(60) << "LIBRARY" << endl;
	cout << "What you want to do?" << endl;
	do
	{
		cout << "add - to add any information\t\tprint - to print any information\tdelete - to remove element by ID\nedit - to full edit information\t\t";
		cout << "search - to search any information\tsort - to sort any information\ngive - to give the book\t\t\treturn - to return the book\t\t";
		cout << "save - to save data in file\nload - to load data from file\t\texit - to finish" << endl;
		cout << "->";
		cin.getline(buf, 50);
		//to add a book or reader
		if (strcmp(buf, "add") == 0)
		{
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ADDITION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			do
			{
				cout << "book - to add a book\t\treader - to add a reader\t\tfinish - to finish the addition" << endl;
				cout << "add->";
				cin.getline(buf, 50);
				if (strcmp(buf, "book") == 0)
					add_Book(b_arr, b_size, b_id);
				if (strcmp(buf, "reader") == 0)
					add_Reader(r_arr, r_size, r_id);
			} while (strcmp(buf, "finish") != 0);
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		//to delete a book or reader by id
		if (strcmp(buf, "delete") == 0)
		{
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DELETION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			do
			{
				int id_del;
				cout << "book - to delete book by ID\t\treader - to delete reader by ID\t\tfinish - to finish the deleting" << endl;
				cout << "delete->";
				cin.getline(buf, 50);
				if (strcmp(buf, "book") == 0)
				{
					cout << "Enter the ID for delete->";
					cin >> id_del;
					cin.ignore();
					del_Book_by_id(b_arr, b_size, id_del);
				}
				if (strcmp(buf, "reader") == 0)
				{
					cout << "Enter the ID for delete->";
					cin >> id_del;
					cin.ignore();
					del_Reader_by_id(r_arr, r_size, id_del);
				}
			} while (strcmp(buf, "finish") != 0);
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		//to print a books or readers
		if (strcmp(buf, "print") == 0)
		{
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PRINT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			do
			{
				cout << "book - to print any information about book\t\treader - to print any information about reader\nfinish - to finish the print" << endl;
				cout << "print->";
				cin.getline(buf, 50);
				if (strcmp(buf, "book") == 0)
				{
					cout << "list - to print a list of all books\t\t\tpopular - to print the most popular books in their genre\nreaders - to print books that the reader has" << endl;
					cout << "print book->";
					cin.getline(buf, 50);
					if (strcmp(buf, "list") == 0)
					{
						for (int i = 0; i < b_size; i++)
						{
							print_Book(b_arr[i], r_arr, r_size);
						}
					}
					if (strcmp(buf, "popular") == 0)
						print_most_popular_book_in_genre(b_arr, b_size, r_arr, r_size);
					if (strcmp(buf, "readers") == 0)
						print_book_readers_read(b_arr, b_size, r_arr, r_size);
				}
				if (strcmp(buf, "reader") == 0)
				{
					cout << "list - to print a list of all readers\t\t\tactive - to print the most active resders\nexpired - to print readers with an expired book return date" << endl;
					cout << "print reader->";
					cin.getline(buf, 50);
					if (strcmp(buf, "list") == 0)
					{
						for (int i = 0; i < r_size; i++)
						{
							print_Reader(r_arr[i], b_arr, b_size);
						}
					}
					if (strcmp(buf, "active") == 0)
						print_most_active_reader(r_arr, r_size, b_arr, b_size);
					if (strcmp(buf, "expired") == 0)
						print_reader_that_have_expired_return_data(b_arr, b_size, r_arr, r_size);
				}
			} while (strcmp(buf, "finish") != 0);
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		//to edit (full/partial) a books or readers by id
		if (strcmp(buf, "edit") == 0)
		{
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EDITING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			do
			{
				cout << "book - to edit information about book\treader - to edit information about reader\tfinish - to finish editing" << endl;
				cout << "edit->";
				cin.getline(buf, 50);
				if (strcmp(buf, "book") == 0)
				{
					int id_edit;
					cout << "\t\t\tpart - to partial editing\t\tfull - to full editing" << endl;
					cout << "edit book->";
					cin.getline(buf, 50);
					if (strcmp(buf, "part") == 0)
					{
						cout << "Enter the book ID for editing->";
						cin >> id_edit;
						part_Book_edit(b_arr, b_size, id_edit);
					}
					if (strcmp(buf, "full") == 0)
					{
						cout << "Enter the book ID for editing->";
						cin >> id_edit;
						full_Book_edit(b_arr, b_size, id_edit);
					}
				}
				if (strcmp(buf, "reader") == 0)
				{
					int id_edit;
					cout << "\t\t\tpart - to partial editing\t\tfull - to full editing" << endl;
					cout << "edit reader->";
					cin.getline(buf, 50);
					if (strcmp(buf, "part") == 0)
					{
						cout << "Enter the reader ID for editing->";
						cin >> id_edit;
						part_Reader_edit(r_arr, r_size, id_edit);
					}
					if (strcmp(buf, "full") == 0)
					{
						cout << "Enter the reader ID for editing->";
						cin >> id_edit;
						full_Reader_edit(r_arr, r_size, id_edit);
					}
				}
			} while (strcmp(buf, "finish") != 0);
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		//to search a books or readers by some parameters
		if (strcmp(buf, "search") == 0)
		{
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SEARCH ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			do
			{
				cout << "book - to search books by parameter\treader - to search readers by parameter\t\tfinish - to end the search" << endl;
				cout << "search->";
				cin.getline(buf, 50);
				if (strcmp(buf, "book") == 0)
				{
					cout << "author - to search book by author\ttitle - to search the book by title\ngenre - to search book by genre\t\tpopular - to search book by popularity" << endl;
					cout << "search book->";
					cin.getline(buf, 50);
					if (strcmp(buf, "author") == 0)
						search_Book_by_author(b_arr, b_size, r_arr, r_size);
					if (strcmp(buf, "title") == 0)
						search_Book_by_title(b_arr, b_size, r_arr, r_size);
					if (strcmp(buf, "genre") == 0)
						search_Book_by_genre(b_arr, b_size, r_arr, r_size);
					if (strcmp(buf, "popular") == 0)
						search_Book_by_popular(b_arr, b_size, r_arr, r_size);
				}
				if (strcmp(buf, "reader") == 0)
				{
					cout << "name - to search by name\t\tread - to search by the number of books read\nid - to search by reader ID\t\tpassport - to search by passport number" << endl;
					cout << "search->";
					cin.getline(buf, 50);
					if (strcmp(buf, "name") == 0)
					{
						int i = search_Reader_by_full_name(r_arr, r_size);
						print_Reader(r_arr[i], b_arr, b_size);
					}
					if (strcmp(buf, "read") == 0)
						search_Reader_by_num_book_read(r_arr, r_size, b_arr, b_size);
					if (strcmp(buf, "id") == 0)
					{
						int i = search_Reader_by_id(r_arr, r_size);
						print_Reader(r_arr[i], b_arr, b_size);
					}
					if (strcmp(buf, "passport") == 0)
					{
						int i = search_Reader_by_passport(r_arr, r_size);
						print_Reader(r_arr[i], b_arr, b_size);
					}
				}
			} while (strcmp(buf, "finish") != 0);
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		//to sort a books or readers by some parameters
		if (strcmp(buf, "sort") == 0)
		{
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SORTING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			do
			{
				cout << "book - to sort book by parameter\treader - to sort readers by parameter\tfinish - to end the sort" << endl;
				cout << "sort->";
				cin.getline(buf, 50);
				if (strcmp(buf, "book") == 0)
				{
					cout << "author - to sort book by author\t\ttitle - to sort the book by title\ngenre - to sort book by genre\t\tpopular - to sort book by popularity" << endl;
					cout << "sort book->";
					cin.getline(buf, 50);
					if (strcmp(buf, "author") == 0)
						sort_Book_by_author(b_arr, b_size, r_arr, r_size);
					if (strcmp(buf, "title") == 0)
						sort_Book_by_name(b_arr, b_size, r_arr, r_size);
					if (strcmp(buf, "genre") == 0)
						sort_Book_by_genre(b_arr, b_size, r_arr, r_size);
					if (strcmp(buf, "popular") == 0)
						sort_Book_by_popular(b_arr, b_size, r_arr, r_size);
				}
				if (strcmp(buf, "reader") == 0)
				{
					cout << "name - to sort by name\t\t\tread - to sort by the number of books read\nid - to sort by reader ID\t\tpassport - to sort by passport number" << endl;
					cout << "sort reader->";
					cin.getline(buf, 50);
					if (strcmp(buf, "name") == 0)
						sort_Reader_by_name(r_arr, r_size, b_arr, b_size);
					if (strcmp(buf, "read") == 0)
						sort_Reader_by_num_book_read(r_arr, r_size, b_arr, b_size);
					if (strcmp(buf, "id") == 0)
						sort_Reader_by_ID(r_arr, r_size, b_arr, b_size);
					if (strcmp(buf, "passport") == 0)
						sort_Reader_by_passportID(r_arr, r_size, b_arr, b_size);
				}
			} while (strcmp(buf, "finish") != 0);
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
		//to give a book
		if (strcmp(buf, "give") == 0)
			give_book(b_arr, r_arr, b_size, r_size);
		//to return a book
		if (strcmp(buf, "return") == 0)
			return_book(b_arr, r_arr, b_size, r_size);
		//to save data about a books or readers in file
		if (strcmp(buf, "save") == 0)
		{
			FILE* f_w = fopen("library.bin", "wb");
			if (f_w)
			{
				Save(f_w, b_arr, b_size, r_arr, r_size);
				fclose(f_w);
			}
			else
				cout << "The file did not open!" << endl;
		}
		//to load data about a books or readers from file
		if (strcmp(buf, "load") == 0)
		{
			FILE* f_r = fopen("library.bin", "rb");
			if (f_r)
			{
				Load(f_r, b_arr, b_size, b_id, r_arr, r_size, r_id);
				fclose(f_r);
			}
			else
				cout << "The file did not open!" << endl;
		}
	} while (strcmp(buf, "exit") != 0);
}