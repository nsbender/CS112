/* StackTester.h declares a test-class for a dynamically allocated (array) Stack.
 * Joel Adams, for CS 112 at Calvin College
 */

#ifndef STACKTESTER_H_
#define STACKTESTER_H_


class StackTester {
public:
	void runTests();
	void testConstructor();
	void testIsEmpty();
	void testPushAndIsFull();
	void testGetTop();
	void testPop();
	void testGetSize();
	void testCopyConstructor();
	void testAssignment();
	void testDestructor();
	void testGetCapacity();
	void testSetCapacity();
	void testDecode();
};

#endif /*STACKTESTER_H_*/

