/* MatrixTester.h declares test-methods for class Matrix.
 * Joel C. Adams, for CS 112 at Calvin College.
 * Student: Landon Sterk
 * Date: March 3, 2015
 */
 
#ifndef PROJECT4_MATRIXTESTER_H_
#define PROJECT4_MATRIXTESTER_H_

#include "Matrix.h"

class MatrixTester {
public:
	void runTests();
	void testDefaultConstructor();
	void testExplicitConstructor();
	void testCopyConstructor();
	void testAssignment();
	void testEquality();
	void testInequality();
	void testSubscripts();
	void testReadSubscript(const Matrix<Item>& mat);
	void testTranspose();
	void testAddition();
	void testSubtraction();
	void testMultiply();
	void testReadFromStream();
	void testReadFromFile();
	void testWriteToStream();
	void testWriteToFile();
};

#endif /*PROJECT4_MATRIXTESTER_H_*/
