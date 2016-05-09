/* MatrixTester.h declares a class to test Matrix operations.
 * Author: Joel C. Adams, for CS 112 at Calvin College.
 * Copyright 2009, Joel C. Adams.  All rights reserved.
 */

#ifndef MATRIXTESTER_H_
#define MATRIXTESTER_H_

#include "Matrix.h"

class MatrixTester {
public:
	void runTests();
	void testConstructor();
	void testEquality();
	void testCopyConstructor();
	void testAssignment();
	void testAddition();
	void testTranspose();
};

#endif /*MATRIXTESTER_H_*/
