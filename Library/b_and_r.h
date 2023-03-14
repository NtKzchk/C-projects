#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<iomanip>
#include"books.h"
#include"readers.h"
using namespace std;

void print_Book(Book obj, Reader* arr, int size);
void print_Reader(Reader obj, Book* arr, int size);
void give_book(Book*& b_arr, Reader*& r_arr, int b_size, int r_size);
void return_book(Book*& b_arr, Reader*& r_arr, int b_size, int r_size);
void print_book_readers_read(Book* b_arr, int b_size, Reader* r_arr, int r_size);

void search_Book_by_author(Book* b_arr, int b_size, Reader* r_arr, int r_size);
void search_Book_by_title(Book* b_arr, int b_size, Reader* r_arr, int r_size);
void search_Book_by_genre(Book* b_arr, int b_size, Reader* r_arr, int r_size);
void search_Book_by_popular(Book* b_arr, int b_size, Reader* r_arr, int r_size);
void search_Reader_by_num_book_read(Reader* r_arr, int r_size, Book* b_arr, int b_size);

void print_most_active_reader(Reader* r_arr, int r_size, Book* b_arr, int b_size);
void print_most_popular_book_in_genre(Book* b_arr, int b_size, Reader* r_arr, int r_size);
void print_reader_that_have_expired_return_data(Book* b_arr, int b_size, Reader* r_arr, int r_size);

void sort_Reader_by_num_book_read(Reader*& r_arr, int r_size, Book* b_arr, int b_size);
void sort_Reader_by_ID(Reader*& r_arr, int r_size, Book* b_arr, int b_size);
void sort_Reader_by_passportID(Reader*& r_arr, int r_size, Book* b_arr, int b_size);
void sort_Reader_by_name(Reader*& r_arr, int r_size, Book* b_arr, int b_size);

void sort_Book_by_author(Book*& b_arr, int b_size, Reader* r_arr, int r_size);
void sort_Book_by_name(Book*& b_arr, int b_size, Reader* r_arr, int r_size);
void sort_Book_by_genre(Book*& b_arr, int b_size, Reader* r_arr, int r_size);
void sort_Book_by_popular(Book*& b_arr, int b_size, Reader* r_arr, int r_size);

void Save(FILE*& f, Book* b_arr, int b_size, Reader* r_arr, int r_size);
void Load(FILE* f, Book*& b_arr, int& b_size, Reader*& r_arr, int& r_size);
void menu(Book*& b_arr, int& b_size, int& b_id, Reader*& r_arr, int& r_size, int& r_id);