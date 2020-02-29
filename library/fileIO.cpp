#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(vector<book> &books, const char *filename) {
	ifstream bookIn(filename);

	if (!bookIn.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	books.clear();
	string newLine;

	while (getline(bookIn, newLine)) {
		if (newLine.size() > 0) {
			stringstream currentLine(newLine);
			vector<string> bookDetails;

			while (currentLine.good()) {
				string subString;
				getline(currentLine, subString, ',');
				bookDetails.push_back(subString);
			}
			auto newBook = book();
			newBook.book_id = stoi(bookDetails[0]);
			newBook.title = bookDetails[1];
			newBook.author = bookDetails[2];
			newBook.state = (book_checkout_state) stoi(bookDetails[3]);
			newBook.loaned_to_patron_id = stoi(bookDetails[4]);
			books.push_back(newBook);
		}
	}
	bookIn.close();

	if (books.size() <= 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(vector<book> &books, const char *filename) {
	if (books.size() <= 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	ofstream bookOut(filename);

	if (!bookOut.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	for (uint i = 0; i < books.size(); i++) {
		auto currentBook = books[i];
		string bookLine;
		bookLine = to_string(currentBook.book_id) + "," + currentBook.title
				+ "," + currentBook.author + "," + to_string(currentBook.state)
				+ "," + to_string(currentBook.loaned_to_patron_id);
		bookOut << bookLine << endl;
	}
	bookOut.close();
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(vector<patron> &patrons, const char *filename) {
	ifstream patronsIn(filename);

	if (!patronsIn.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	patrons.clear();
	string newLine;

	while (getline(patronsIn, newLine)) {
		if (newLine.size() > 0) {
			stringstream currentLine(newLine);
			vector<string> patronDetails;

			while (currentLine.good()) {
				string subString;
				getline(currentLine, subString, ',');
				patronDetails.push_back(subString);
			}
			auto newPatron = patron();
			newPatron.patron_id = stoi(patronDetails[0]);
			newPatron.name = patronDetails[1];
			newPatron.number_books_checked_out = stoi(patronDetails[2]);
			patrons.push_back(newPatron);
		}
	}
	patronsIn.close();

	if (patrons.size() <= 0) {
		return NO_PATRONS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(vector<patron> &patrons, const char *filename) {
	if (patrons.size() <= 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	ofstream patronOut(filename);

	if (!patronOut.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	for (uint i = 0; i < patrons.size(); i++) {
		auto currentPatron = patrons[i];
		string patronLine;
		patronLine = to_string(currentPatron.patron_id) + ","
				+ currentPatron.name + ","
				+ to_string(currentPatron.number_books_checked_out);
		patronOut << patronLine << endl;
	}
	patronOut.close();
	return SUCCESS;
}

