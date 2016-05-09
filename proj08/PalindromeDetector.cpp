/*
 * PalindromeDetector.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: nsb2
 */

#include "PalindromeDetector.h"
#include "Stack.h"

void PalindromeDetector::detectPalindromes(string inputFile, string outputFile) {
	/*
	 * Tests a text file for palindromes and outputs them to a new file
	 * @param : string inputFile and string outputFile, the 2 files being read from and written to
	 * Preconditions: Text files must exist
	 * Return: Void
	 */
	string currentLine;
	ifstream fin;
	ofstream fout;

	fin.open(inputFile.c_str());
	assert(fin.is_open());
	fout.open(outputFile.c_str());
	assert(fout.is_open());

	while (! fin.eof()) { // Iterates through a text file line by line
		getline(fin,currentLine);
		fout << currentLine << flush; // Outputs the current line to a new file
		if ( isPalindrome(currentLine) == true ) {
			fout << " ***" << endl; // Marks the line with *** if it is a palindrome based on isPalindrome()
		}
		else {
			fout << endl; // If it is not a palindrome, it is not marked and the function continues.
		}
	}

	fin.close();
	fout.close();
}

bool PalindromeDetector::isPalindrome(string line) {
	/*
	 * Tests to see if a line is a palindrome
	 * @param : string line, the line being tested
	 * Preconditions: line must be a non-empty string
	 * Return: bool depending on whether the string is a palindrome or not
	 */
	Stack<char> charStack(1);
	ArrayQueue<char> charQueue(1);
	char ch1;
	char ch2;

	for(unsigned i = 0 ; i < line.length() ; i++) {
		if ( // Test to make sure that the character is actually a letter
				isspace(line.at(i)) == false
				&& line.at(i) != ','
				&& line.at(i) != '.'
				&& line.at(i) != '\''
				&& line.at(i) != '!')
		{
			try { // Test to see if the char can be put in the stack
				charStack.push(tolower(line.at(i)));
			}
			catch(...) { // If the char cannot fit, the Stack is resized and the char is pushed
				charStack.setCapacity(charStack.getCapacity()*2);
				charStack.push(tolower(line.at(i)));
			}
			try { // Test to see if the char can be put in the queue
				charQueue.append(tolower(line.at(i)));
			}
			catch(...) { // If the char cannot fit, the Queue is resized and the char is pushed
				charQueue.setCapacity(charQueue.getCapacity()*2);
				charQueue.append(tolower(line.at(i)));
			}
		}
	}
	while (charStack.getSize() > 0 && charQueue.getSize() > 0) { //While the Stack and Queue are not empty, their top item is added to a char variable.
		ch1 = charStack.pop();
		ch2 = charQueue.remove();
		if ( ch1 != ch2 ){ // If the chars on 'top' of each structure are not the same, false is returned, since it cannot be a palindrome
			return false;
		}
	}
	return true; // If all characters are the same, true is returned
}
