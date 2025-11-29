#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Book {
private:
	string title;
	string author;
	int count;

public:
	Book(string t, string a, int i) : title(t), author(a), count(i) {}

	string getTitle() const noexcept {
		return title;
	}

	string getAuthor() const noexcept {
		return author;
	}

	int getCount() const noexcept {
		return count;
	}

	void setCount(int c) {
		if (c < 0) {
			throw invalid_argument("Count cannot be negative");
		}
		else {
			count = c;
		}
	}

	void print() const {
		cout << "Title: " << title << " | "
			<< "Author: " << author << " | "
			<< "Number Available: " << count << endl;
	}
};




#endif
