/* tester.cpp is a "driver" to run the tests in the StackTester class.
 * Joel Adams, for CS 112 at Calvin College.
 */
 
#include "StackTester.h"
#include "Stack.h"
#include "StackException.h"
#include <cassert>
#include <cctype>
#include <stdexcept>
#include <cstdlib>

using namespace std;

/* Method that both tests the Stack functions and encodes a message from a txt file.
 * Parameter: None
 */
void tester() {
	StackTester st;
	st.runTests();
}

int main() {
	tester();

	ifstream fin;
	ofstream fout;
	string line;
	Stack<char> current(1);
	unsigned counter;

	fin.open("original.txt");
	assert( fin.is_open() == true);
	fout.open("encoded.txt");
	assert( fout.is_open() == true);

	while(getline(fin , line)) {
		for (unsigned i = 0 ; i < line.length() ; i++) {
			if (
					isspace(line.at(i)) == false
					&& line.at(i) != ','
					&& line.at(i) != '.'
					&& line.at(i) != '!')
			{
				try {
					current.push(line.at(i));
					counter ++;
				}
				catch(StackException&) { // all inclusive catch() method that catches any and all exceptions
					current.setCapacity(current.getCapacity()*2);
					current.push(line.at(i));
					counter ++;
				}
			}
			else {
				try {
					while (counter > 0){
						fout << current.pop();
						counter --;
					}
					fout << line.at(i);
				}
				catch(...) {

				}
			}
		}
	}
	cout << "File 'original.txt' has been encoded and outputted to 'encoded.txt.'" ;
}





