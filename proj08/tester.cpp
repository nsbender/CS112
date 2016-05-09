/* tester.cpp drives the testing of the Queue classes.
 * Joel Adams, for CS 112 at Calvin College.
 * Student name: Nate Bender
 * Date: 4/17/15
 */

#include "ArrayQueueTester.h"
#include "LinkedQueueTester.h"
#include "PalindromeDetector.h"
#include <iostream>

int main() {
	ArrayQueueTester aqt;
	aqt.runTests();
	LinkedQueueTester lqt;
	lqt.runTests();

	PalindromeDetector pdt;
	pdt.detectPalindromes("lines.txt","linesMarked.txt");
	cout << "\"Lines.txt\" has been read for palindromes and the result has been written to \"linesMarked.txt\"" << endl;
}


