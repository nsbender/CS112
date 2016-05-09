/* CollectionTester.cpp defines the MovieCollection test-methods.
 * Student Name: Nate Bender
 * Date: 10 February 2015
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "CollectionTester.h"
#include "MovieCollection.h"

void CollectionTester::runTests() const {
   cout << "Testing class MovieCollection..." << endl;
   testConstructor();
   cout << "All tests passed!" << endl;
}

void CollectionTester::testConstructor() const {
    cout << "- constructor..." << flush;
    MovieCollection mc("testCollection.txt");
    // case of 1 movie
    vector<Movie> v1 = mc.searchByDirector("Hand");
    assert( v1.size() == 1 );
    assert( v1[0].getTitle() == "Bambi" );
    cout << " 1 " << flush;
    // case of 2 movies
    vector<Movie> v2 = mc.searchByDirector("Spielberg");
    assert( v2.size() == 2 );
    assert( v2[0].getTitle() == "Jaws" );
    assert( v2[1].getTitle() == "Raiders of the Lost Ark" );
    cout << " 2 " << flush;
    // case of no movies
    vector<Movie> v3 = mc.searchByDirector("Hitchcock");
    assert( v3.size() == 0 );
    cout << " 3 " << flush;
    cout << " Passed!" << endl;
}
