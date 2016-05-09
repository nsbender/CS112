/* ListTester.h declares the test-class for class List.
 * Joel Adams, for CS 112 at Calvin College.
 */

#ifndef LISTTESTER_H_
#define LISTTESTER_H_

class ListTester {
public:
	void runTests() const;
	void testDefaultConstructor() const;
	void testNodeDefaultConstructor() const;
	void testNodeExplicitConstructor() const;
	void testAppend() const;
	void testDestructor() const;
	void testCopyConstructor() const;
	void testAssignment() const;
	void testEquality() const;
	void testInequality() const;
	void testReadFromStream() const;
	void testWriteToStream() const;
	void testReadFromFile() const;
	void testWriteToFile() const;
	void testPrepend() const;
	void testGetIndexOf() const;
	void testInsert() const;
	void testRemove() const;
	void testSort() const; // Partner was unable to complete
	void testMerge() const; // Partner was unable to complete
};

#endif /*LISTTESTER_H_*/
