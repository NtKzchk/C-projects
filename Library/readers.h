#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

struct Reader
{
	//reader is
	int id = 0;
	//reader last name
	char* l_name;
	//reader middle name
	char* m_name;
	//reader first name
	char* f_name;
	//day of birth of the reader
	int day;
	//month of birth of the reader
	char* month;
	//year of birth of the reader
	int year;
	//reader number of passport
	int passport_id;
	//the number of books read
	int num_book_read = 0;
	//the books the reader reads
	int list_book[5]{};
};
int get_Reader_index(Reader* arr, int size, int id);
void input_Reader(Reader& obj);
void add_Reader(Reader*& arr, int& size, int& id);
void del_Reader_by_id(Reader*& arr, int& size, int del_id);
void full_Reader_edit(Reader*& arr, int size, int id);
void part_Reader_edit(Reader*& arr, int size, int id);
int search_Reader_by_full_name(Reader* r_arr, int r_size);
int search_Reader_by_id(Reader* r_arr, int r_size);
int search_Reader_by_passport(Reader* r_arr, int r_size);