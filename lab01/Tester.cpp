/* tester.cpp tests the classes in our project.
 *
 */

#include "MovieTester.h"
#include "CollectionTester.h"
#include <iostream>
using namespace std;

int main() {
    MovieTester mt;
    mt.runTests();
    CollectionTester ct;
    ct.runTests();
}

