#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//enumeration of all possible genres
enum Genre
{
	Fantasy, Sci_Fi, Mystery, Romance, Horror, History, Health, Humor, Unknown
};
struct Book
{
	//book id
	int id = 0;
	//book publication day
	int day;
	//book publication month
	char* month;
	//book publication year
	int year;
	//book title
	char* name;
	//book author
	char* author_name;
	//book genre
	Genre genre;
	//book cost
	int cost;
	//book rating
	double rating;
	//ID of the reader who has the book
	int id_reader = 0;
	//while taking books
	time_t time_took_book = 0;
	//book popular
	int popular = 0;
};
Genre str_to_genre(const char* str);
const char* genre_to_str(Genre s);
int get_Book_index(Book* arr, int size, int id);
void input_Book(Book& obj);
void add_Book(Book*& arr, int& size, int& id);
void del_Book_by_id(Book*& arr, int& size, int del_id);
void full_Book_edit(Book*& arr, int size, int id);
void part_Book_edit(Book*& arr, int size, int id);