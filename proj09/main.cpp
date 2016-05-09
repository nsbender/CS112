
#include "BST_Tester.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;



void runTests() {
	BST_Tester bstt;
	bstt.runTests();
}

void height() {
	string fileName;
	ifstream fin;
	string line;
	long int value;
	BST<long int> bst;
	unsigned duplicates;
	cout << "Please enter the name of the file containing values that you would like inserted into a Binary Search Tree." << endl;
	cin >> fileName;
	fin.open(fileName.c_str());
	assert( fin.is_open() );

	while (!fin.eof()) {
		getline(fin,line);
		value = atoi(line.c_str()); //used to convert getline into an int.
		try {
			bst.insert(value);
		}
		catch(Exception& e) {
			duplicates ++;
		}
	}

	cout << "Height of the loaded BST is: " << bst.getHeight() << endl;
	cout << "There were " << duplicates << " duplicates" << endl;
	fin.close();
	duplicates = 0;
}

int main() {
	int choice;

	cout << "Press 1 to run tests, and 2 to create a Binary Search Tree and find its height, and any other key to exit" << endl;
	cin >> choice;

	if (choice == 1) {
		runTests();
	}
	if (choice == 2) {
		height();
	}
	else {
		cout << "exiting." << flush;
		return 1;
	}

}
