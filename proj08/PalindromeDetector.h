/*
 * PalindromeDetector.h
 *
 *  Created on: Apr 21, 2015
 *      Author: nsb2
 */

#ifndef PALINDROMEDETECTOR_H_
#define PALINDROMEDETECTOR_H_

#include "ArrayQueue.h"
#include <fstream>
#include <cassert>

using namespace std;

class PalindromeDetector {
public:
	void detectPalindromes(string inputFile, string outputFile);
	bool isPalindrome(string line);
};

#endif /* PALINDROMEDETECTOR_H_ */
