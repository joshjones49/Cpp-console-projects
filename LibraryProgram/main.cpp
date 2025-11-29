#include <iostream>
#include "person.h"
#include <string>

using namespace std;

void checkAccess(Person p);
vector<Person> seedPersonData();
vector<Book> seedBookData();
Person login(vector<Person> people, int id);
void displayWelcomeMsg(const Person& p);
Book createBook(string title, string author, int count);
Person createPerson(string name, int age, string access, int id);

int main() {
	// seed data =============================>
	vector<Book> books = seedBookData();
	vector<Person> people = seedPersonData();

	string adminCmds[9] = {
		"-out | log out", "-addb | add a book",
		"-addu | add a user", "-co | check out book",
		"-cmds | list commands", "-lb | list books",
		"-lu | list users", "-rb | return book", 
		"-sd | ends program"
	};

	string userCmds[4] = {
		"-out | log out", "-cmds | list commands",
		"-lb | list books", "-sd | ends program"
	};

	Person user("", 0, "", 0);

	bool userLoggedIn = false;
	bool adminLoggedIn = false;
	bool programRunning = true;

	int currentUser;
	cout << "Enter User ID: ";
	cin >> currentUser;
	currentUser--; // adjust for 0 index
	try {
		user = login(people, currentUser);
		if (user.getAccess() == "Admin") {
			adminLoggedIn = true;
			userLoggedIn = false;
		}
		else {
			userLoggedIn = true;
			adminLoggedIn = false;
		}
		checkAccess(user);
		displayWelcomeMsg(user);
	} catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}

	while (programRunning) {
		if (!userLoggedIn && !adminLoggedIn) {
			cout << endl;
			cout << "Enter User ID: ";
			cin >> currentUser;
			currentUser--; // adjust for 0 index

			try {
				user = login(people, currentUser);
				if (user.getAccess() == "Admin") {
					adminLoggedIn = true;
					userLoggedIn = false;
				}
				else {
					userLoggedIn = true;
					adminLoggedIn = false;
				}
				checkAccess(user);
				displayWelcomeMsg(user);
			}
			catch (const exception& e) {
				cerr << "Error: " << e.what() << endl;
				return 1;
			}
		}

		string command;
		cout << endl;
		cout << "Enter Command:" << endl;
		cout << boolalpha;
		cout << userLoggedIn << endl;
		cout << adminLoggedIn << endl;
		cout << endl;
		cin >> command;

		if (adminLoggedIn) {
			if (command == "-out") {
				cout << endl;
				cout << "Logging Out: " << user.getName() << endl;
				adminLoggedIn = false;
			}
			else if (command == "-cmds") {
				cout << "Available commands:" << endl;
				cout << "====================================" << endl;
				for (const string& cmd : adminCmds) {
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

			}
			else if (command == "-lb") {
				cout << "Books in Inventory:" << endl;
				cout << "====================================" << endl;
				for (Book b : books) {
					b.print();
				}
			}
			else if (command == "-addu") {
				string name;
				int age;
				string access;
				int id;
				cout << "Enter user details" << endl;
				cout << "Name: ";
				cin.ignore();
				getline(cin, name);
				cout << "Age: ";
				cin >> age;
				cout << "Access Level (Admin/User): ";
				cin >> access;
				cout << "ID: ";
				cin >> id;
				people.push_back(createPerson(name, age, access, id));
			}
			else {
				cout << "Invalid command. Use -cmds to list commands." << endl;
				cout << endl;
			}
		}
		else {
			if (command == "-out") {
				cout << endl;
				cout << "Logging Out: " << user.getName() << endl;
				userLoggedIn = false;
			}
			else if (command == "-cmds") {
				cout << "Available commands:" << endl;
				cout << "====================================" << endl;
				for (const string& cmd : userCmds) {
					cout << cmd << endl;
				}
			}
			else if (command == "-lb") {
				cout << "Books in Inventory:" << endl;
				cout << "====================================" << endl;
				for (Book b : books) {
					b.print();
				}
			}
			else {
				cout << "Invalid command. Use -cmds to list commands." << endl;
				cout << endl;
			}	
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

void displayWelcomeMsg(const Person& p) {
	if (p.getAccess() == "Admin") {
		cout << "==========================" << endl;
		cout << "Welcome: " << p.getName() << endl;
		cout << "==========================" << endl;
		cout << endl;
		cout << "Use -cmds to list commands" << endl;
	}
	else {
		cout << "==========================" << endl;
		cout << "Welcome: " << p.getName() << endl;
		cout << "==========================" << endl;
		cout << endl;
		cout << "Use -cmds to list commands" << endl;
	}
}

Book createBook(string title, string author, int count) {
	Book b(title, author, count);
	cout << "Book added to inventory" << endl;
	cout << endl;
	return b;
}

Person createPerson(string name, int age, string access, int id) {
	Person p(name, age, access, id);
	cout << "User created: " << name << endl;
	cout << endl;
	return p;
}
