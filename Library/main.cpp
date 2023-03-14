#include"b_and_r.h";
#include"books.h"
#include"readers.h"

int main()
{
	int book_size = 0, book_id = 1, reader_size = 0, reader_id = 1;
	Book* book = new Book[book_size];
	Reader* reader = new Reader[reader_size];
	menu(book, book_size, book_id, reader, reader_size, reader_id);
	for (int i = 0; i < book_size; i++)
	{
		delete[]book[i].name;
		delete[]book[i].author_name;
		delete[]book[i].month;
	}
	delete[]book;
	for (int i = 0; i < reader_size; i++)
	{
		delete[]reader[i].f_name;
		delete[]reader[i].m_name;
		delete[]reader[i].l_name;
		delete[]reader[i].month;
	}
	delete[]reader;
}