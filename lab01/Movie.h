/* Movie.h
 * Student Name: Nate Bender
 * Date: 10 February 2015
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>
#include <fstream>
#include <cassert>
using namespace std;

class Movie {
public:
   Movie();
   Movie(const string& title, int year, const string& director);
   string getTitle() const;
   int getYear() const;
   string getDirector() const;
   void readFrom(istream& in);
   void writeTo(ostream& out) const;
private:
   string myTitle;
   int    myYear;
   string myDirector;
};

#endif /*MOVIE_H_*/
