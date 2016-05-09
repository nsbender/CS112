/* VecTester.h provides unit tests for Vec, a simple vector class.
 * Student Name: Landon Sterk
 * Date: February 24, 2015
 * CS 112 Lab 03
 * Begun by: Joel C. Adams, for CS 112 at Calvin College. No edits made by student
 */
 
#ifndef PROJECT4_VECTESTER_H_
#define PROJECT4_VECTESTER_H_

#include "Vec.h"

class VecTester {
public:
	void runTests() const;
	void testDefaultConstructor() const;
	void testExplicitConstructor() const;
	void testDestructor() const;
	void testGetSize() const;
	void testSetItem() const;
	void testGetItem() const;
	void testSetSize() const;
	void testCopyConstructor() const;
	void testAssignment() const;
	void testEquality() const;
	void testWriteToStream() const;
	void testReadFromStream() const;
	void testInequality() const;
	void testAddition() const;
	void testSubtraction() const;
	void testDotProduct() const;
	void testReadFromFile() const;
	void testWriteToFile() const;
};

#endif /*PROJECT4_VECTESTER_H_*/
