#include <iostream>
#include "person.h"
#include <string>

using namespace std;

void checkAccess(Person p);
vector<Person> seedPersonData();
vector<Book> seedBookData();
Person login(vector<Person> people, int id);
void displayWelcomeMsg(const Person& admin, bool isDisplayed);
Book createBook(string title, string author, int count);

int main() {
	// seed data =============================>
	vector<Book> books = seedBookData();
	vector<Person> people = seedPersonData();
	string commands[6] = {
		"-out | log out", "-addb | add a book",
		"-addu | add a user", "-co | check out a book",
		"-cmds | list commands", "-lb | list books"
	};

	Person admin("", 0, "", 0);

	bool adminLoggedIn = false;
	bool displayWelcome = true;

	int currentUser;
	cout << "Enter User ID: ";
	cin >> currentUser;
	currentUser--; // adjust for 0 index
	try {
		admin = login(people, currentUser);
		checkAccess(admin);
		adminLoggedIn = true;
	} catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}

	while (adminLoggedIn) {
		string command;
		displayWelcomeMsg(admin, displayWelcome);
		cout << endl;
		cout << "Enter Command:" << endl;
		cout << endl;
		cin >> command;
		if (command == "-out") {
			cout << endl;
			cout << "Logging Out: " << admin.getName() << endl;
			adminLoggedIn = !adminLoggedIn;
		}
		else if (command == "-cmds") {
			cout << "Available commands:" << endl;
			cout << "====================================" << endl;
			for (const auto& cmd : commands) {
				cout << cmd << endl;
			}
		}
		else if (command == "-addb") {
			string title;
			string author;
			int count;
			cout << "Enter book details" << endl;
			cout << "Title: ";
			cin.ignore();
			getline(cin, title);
			cout << "Author: ";
			getline(cin, author);
			cout << "Count: ";
			cin >> count;
			books.push_back(createBook(title, author, count));
			cout << "====================================" << endl;
			for (Book b : books) {
				b.print();
			}
			displayWelcome = !displayWelcome;

		} else if (command == "-lb") {
			cout << "Books in Inventory:" << endl;
			cout << "====================================" << endl;
			for (Book b : books) {
				b.print();
			}
			displayWelcome = !displayWelcome;
		}
		else {
			cout << "Invalid command. Use -cmds to list commands." << endl;
			cout << endl;
			displayWelcome = !displayWelcome;
		}

	}
	

	return 0;
}

void checkAccess(Person p) {
	if (p.getAccess() == "Admin") {
		cout << "<Access Granted: Admin>" << endl;
	}
	else {
		cout << "<Access Granted: User>" << endl;
	}
}

vector<Person> seedPersonData() {
	vector<Person> people;
	people.push_back(Person("Alice Johnson", 28, "User", 1));
	people.push_back(Person("Bob Smith", 34, "User", 2));
	people.push_back(Person("Charlie Brown", 22, "User", 3));
	people.push_back(Person("Diana Prince", 30, "Admin", 4));
	people.push_back(Person("Ethan Hunt", 40, "User", 5));
	people.push_back(Person("Fiona Gallagher", 27, "User", 6));
	people.push_back(Person("George Martin", 45, "Admin", 7));
	people.push_back(Person("Hannah Baker", 19, "User", 8));
	people.push_back(Person("Ian Fleming", 50, "User", 9));
	return people;
}

vector<Book> seedBookData() {
	vector<Book> books;
	books.push_back(Book("The Great Gatsby", "F. Scott Fitzgerald", 101));
	books.push_back(Book("1984", "George Orwell", 102));
	books.push_back(Book("To Kill a Mockingbird", "Harper Lee", 103));
	books.push_back(Book("Pride and Prejudice", "Jane Austen", 104));
	books.push_back(Book("The Catcher in the Rye", "J.D. Salinger", 105));
	books.push_back(Book("Moby Dick", "Herman Melville", 106));
	books.push_back(Book("War and Peace", "Leo Tolstoy", 107));
	books.push_back(Book("Ulysses", "James Joyce", 108));
	books.push_back(Book("The Odyssey", "Homer", 109));
	books.push_back(Book("Hamlet", "William Shakespeare", 110));
	return books;
}

Person login(vector<Person> people, int id) {
	return people.at(id);
}

void displayWelcomeMsg(const Person& admin, bool isDisplayed) {
	if (isDisplayed) {
		cout << "==========================" << endl;
		cout << "Welcome: " << admin.getName() << endl;
		cout << "==========================" << endl;
		cout << endl;
		cout << "Use -cmds to list commands" << endl;
		isDisplayed = !isDisplayed;
	}
}

Book createBook(string title, string author, int count) {
	Book b(title, author, count);
	cout << "Book added to inventory" << endl;
	cout << endl;
	return b;
}
