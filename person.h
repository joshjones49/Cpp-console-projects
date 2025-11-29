#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <vector>

#include "book.h"

using namespace std;

class Person {
private:
	string name;
	int age;
	string access;
	int id;

public:
	Person(string name, int age, string access, int id) : name(name), age(age), access(access), id(id) {}

	// getters
	string getName() const noexcept{
		return name;
	}

	int getAge() const noexcept {
		return age;
	}

	string getAccess() const noexcept {
		return access;
	}

	vector<Book> getBooks() {
		return books;
	}

	void addBook(Book b) {
		books.push_back(b);
	}

	void printBooks() {
		for (Book b : books) {
			b.print();
		}
	}

	vector<Book> books;

	// print
	void print() const noexcept {
		cout << "Name: " << name << " | " << "Age: " << age << " | " << "Access: " << access << endl;
	}
};








#endif
