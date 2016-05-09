/* MovieCollection.h ...
 * Student Name: Nate Bender
 * Date: 10 February 2015
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include <string>
#include "Movie.h"
#include <vector>
#include <cassert>
using namespace std;

class MovieCollection {
public:
	MovieCollection(const string& fileName);
	vector<Movie> searchByDirector(const string& directorName) const;
private:
	vector<Movie> myMovies;
};
