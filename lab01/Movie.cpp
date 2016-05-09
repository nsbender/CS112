/* Movie.cpp
 * Student Name: Nate Bender
 * Date: 10 February 2015
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

 #include "Movie.h"


Movie::Movie() {
	myTitle = "";
	myYear = 0;
	myDirector = "";
}

string Movie::getTitle() const {
	return myTitle;
}

int Movie::getYear() const {
	return myYear;
}

string Movie::getDirector() const {
	return myDirector;
}


Movie::Movie(const string& title, int year, const string& director) {
	myTitle = title;
	myYear = year;
	myDirector = director;
}


void Movie::readFrom(istream& in) {
	getline(in, myTitle);
	in >> myYear;
	string newLine; getline(in, newLine);
	getline(in, myDirector);
}

void Movie::writeTo(ostream& out) const {
	out << myTitle << '\n'
	    << myYear  << '\n'
	    << myDirector << '\n';
}
