/* StackTester.cpp defines test-methods for the 
 *  dynamically allocated (array) Stack operations
 * Joel Adams, for CS 112 at Calvin College
 */

#include "StackTester.h"
#include "Stack.h"
#include <iostream>  // cout, cerr, ...
#include <cassert>   // assert()
#include <cstdlib>   // exit()
using namespace std;

void StackTester::runTests() {
	cout << "Testing Stack class..." << endl;
	testConstructor();
	testIsEmpty();
	testPushAndIsFull();
	testGetTop();
	testPop();
	testGetSize();
	testGetCapacity();
	testSetCapacity();
	testCopyConstructor();
	testAssignment();
	testDestructor();
	cout << "All tests passed!" << endl;
}

void StackTester::testConstructor() {
	cout << "- Testing constructor... " << flush;
	// invalid parameter
	try {
		Stack<Item> s1(0);
		cerr << "\nConstructed stack of size 0\n";
		exit(1);
	} catch (StackException& se) {
		cout << se << flush;
	}
	cout << " 1 " << flush;
	// valid parameter
	Stack<Item> s2(3);
	cout << " 2 " << flush;
	cout << " Passed!" << endl;
}

void StackTester::testIsEmpty() {
	cout << "- Testing isEmpty()... " << flush;
	// capacity 1
	Stack<Item> s1(1);
	assert( s1.isEmpty() );
	cout << " 1 " << flush;
	// capacity > 1
	Stack<Item> s2(3);
	assert( s2.isEmpty() );
	cout << " 2 " << flush;
	cout << " Passed!" << endl;
}


void StackTester::testPushAndIsFull() {
	cout << "- Testing push()... " << flush;
	// test with capacity 1
	Stack<Item> s1(1);
	s1.push(11);
	assert( !s1.isEmpty() );
	assert( s1.isFull() );
	try {
		s1.push(22);
		cerr << "\npush() worked on a full stack (size 1)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 1 " << flush;
	}
	// test with capacity > 1
	Stack<Item> s2(3);
	s2.push(11);
	s2.push(22);
	s2.push(33);
	try {
		s2.push(44);
		cerr << "\npush() worked on a full stack (size 3)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 2 " << flush;
	}
	cout << " Passed! " << endl;
}

void StackTester::testGetTop() {
	cout << "- Testing getTop()... " << flush;
	// test with empty stack
	Stack<Item> s1(1);
	try {
		s1.getTop();
		cerr << "\ngetTop() worked on empty stack\n";
		exit(1);
	} catch (StackException& se) {
		cout << se << flush;
 		cout << " 1 " << flush;
	}
	// test with capacity 1
	Stack<Item> s2(1);
	s2.push(11);
	assert( s2.getTop() == 11 );
	cout << " 2 " << flush;
	// test with capacity > 1
	Stack<Item> s3(3);
	s3.push(11);
	assert( s3.getTop() == 11 );
	s3.push(22);
	assert( s3.getTop() == 22 );
	s3.push(33);
	assert( s3.getTop() == 33 );
	cout << " 3 " << flush;
	cout << " Passed! " << endl;
}

void StackTester::testPop() {
	cout << "- Testing pop()... " << flush;
	// try empty, capacity 1
	Stack<Item> s1(1);
	assert( s1.isEmpty() );
	try {
		s1.pop();
		cerr << "\npop() worked on empty stack (size 1)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 1 " << flush;
	}
	// try empty, capacity > 1
	Stack<Item> s2(3);
	try {
		s2.pop();
		cerr << "\npop() worked on empty stack (size 3)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 2 " << flush;
	}
	// try non-empty, capacity 1
	Stack<Item> s3(1);
	s3.push(11);
	assert( s3.getTop() == 11 );
	assert( s3.pop() == 11 );
	try {
		s3.pop();
		cerr << "\ns3.pop() worked on empty stack (size 1)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 3 " << flush;
	}
	// try non-empty, capacity > 1
	Stack<Item> s4(3);
	s4.push(11);
	s4.push(22);
	s4.push(33);
	assert( s4.getTop() == 33 );
	assert( s4.pop() == 33 );
	assert( s4.getTop() == 22 );
	assert( s4.pop() == 22 );
	assert( s4.getTop() == 11 );
	assert( s4.pop() == 11 );
	try {
		s4.pop();
		cerr << "\ns4.pop() worked on empty stack (size 3)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 4 " << flush;
	}
	cout << " Passed!" << endl;
}

void StackTester::testGetSize() {
	cout << "- Testing getSize()... " << flush;
	// Testing a stack with a size of 5
	Stack<Item> s1(5);
	for (unsigned i = 1 ; i < 6 ; i++) {
		s1.push((i*11));
	}
	assert( s1.getSize() == 5 );
	cout << " 1 " << flush;
	Stack<Item> s2(10);
	for (unsigned i = 1 ; i < 11 ; i++) {
		s2.push((i*11));
	}
	assert( s2.getSize() == 10 );
	cout << " 2 " << flush;
	cout << " Passed!" << endl;
}

void StackTester::testGetCapacity() {
	cout << "- Testing getCapacity()... " << flush;
	// Testing getCapacity() with a capacity of 1
	Stack<Item> s1(1);
	assert( s1.getCapacity() == 1 );
	cout << " 1 " << flush;
	// Testing getCapacity() with a capacity of 10
	Stack<Item> s2(10);
	assert( s2.getCapacity() == 10 );
	cout << " 2 " << flush;
	cout << " Passed!" << endl;
}

void StackTester::testSetCapacity() {
	cout << "- Testing setCapacity()... " << flush;
	// Testing setCapacity() to a capacity smaller than the original (From 10 to 5)
	Stack<Item> s1(10);
	for (unsigned i = 0 ; i < 10 ; i++) {
		s1.push((i+1)*11);
	}
	s1.setCapacity(5);
	assert( s1.myCapacity == 5 );
	assert( s1.isFull() == true );
	assert( s1.pop() == 55);
	cout << " 1 " << flush;
	cout << " Passed!" << endl;
	// Testing setCapacity() to a capacity larger than the original (From 5 to 10)
	Stack<Item> s2(5);
	for (unsigned i = 0 ; i < 5 ; i++) {
		s2.push((i+1)*11);
	}
	assert( s2.isFull() == true );
	s2.setCapacity(10);
	assert( s2.myCapacity == 10 );
	assert( s2.isFull() == false );
	assert( s2.pop() == 55);
}

void StackTester::testCopyConstructor() {
	cout << "- Testing copy constructor... " << flush;
	// minimal empty Stack
	Stack<Item> s1(1);
	Stack<Item> s2(s1);
	assert( s2.isEmpty() );
	assert( s2.myArray != NULL );
	assert( s2.myCapacity == 1 );
	assert( s2.myArray != s1.myArray );
	cout << " 1 " << flush;
	// minimal non-empty Stack
	Stack<Item> s3(1);
	s3.push(11);
	Stack<Item> s4(s3);
	assert( !s4.isEmpty() );
	assert( s4.isFull() );
	assert( s4.getTop() == 11 );
	assert( s4.myArray != s3.myArray );
	cout << " 2 " << flush;
	// non-minimal, non-empty stack
	Stack<Item> s5(3);
	s5.push(11);
	s5.push(22);
	s5.push(33);
	Stack<Item> s6(s5);
	assert( s6.myCapacity = s5.myCapacity );
	assert( s6.myTop == s5.myTop );
	assert( s6.myArray != s5.myArray );
	assert( s6.pop() == 33 );
	assert( s6.pop() == 22 );
	assert( s6.pop() == 11 );
	assert( s5.getTop() == 33 );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void StackTester::testAssignment() {
	cout << "- Testing assignment... " << flush;
	// minimal empty Stacks, same size
	Stack<Item> s1(1);
	Stack<Item> s2(1);
	s2 = s1;
	assert( s2.isEmpty() );
	assert( s2.myArray != NULL );
	assert( s2.myArray != s1.myArray );
	assert( s2.myCapacity == 1 );
	cout << " 1 " << flush;
	// minimal non-empty Stack to empty Stack, same capacity
	Stack<Item> s3(1);
	s3.push(11);
	Stack<Item> s4(1);
	s4 = s3;
	assert( !s4.isEmpty() );
	assert( s4.isFull() );
	assert( s4.getTop() == 11 );
	assert( s4.myArray != s3.myArray );
	cout << " 2 " << flush;
	// minimal empty stack to non-empty stack, same capacity
	Stack<Item> s5(1);
	Stack<Item> s6(1);
	s6.push(11);
	s6 = s5;
	assert( s6.isEmpty() );
	assert( s6.myArray != NULL );
	assert( s6.myArray != s5.myArray );
	assert( s6.myCapacity == 1 );
	cout << " 3 " << flush;
	// non-minimal non-empty stack to empty stack, different capacities
	Stack<Item> s7(3);
	s7.push(11);
	s7.push(22);
	s7.push(33);
	Stack<Item> s8(2);
	s8 = s7;
	assert( s8.myArray != s7.myArray );
	assert( s8.myCapacity == s7.myCapacity );
	assert( s8.myTop == s7.myTop );
	assert( s8.pop() == 33 );
	assert( s8.pop() == 22 );
	assert( s8.pop() == 11 );
	assert( s7.getTop() == 33 );
	cout << " 4 " << flush;
	// non-minimal, empty stack to non-empty stack, different capacities
	Stack<Item> s9(2);
	Stack<Item> s10(3);
	s10.push(11);
	s10.push(22);
	s10.push(33);
	s10 = s9;
	assert( s10.isEmpty() );
	assert( s10.myArray != s9.myArray );
	assert( s10.myCapacity == s10.myCapacity );
	cout << " 5 " << flush;
	// self-assignment, minimal size
	Stack<Item> s11(1);
	s11.push(11);
	s11 = s11;
	assert( s11.isFull() );
	assert( !s11.isEmpty() );
	cout << " 6 " << flush;
	// chaining
	Stack<Item> s12(2);
	s12.push(11);
	s12.push(22);
	Stack<Item> s13(1);
	Stack<Item> s14(1);
	s14 = s13 = s12;
	assert( s14.isFull() );
	assert( s14.myArray != s13.myArray );
	assert( s14.myArray != s12.myArray );
	assert( s14.pop() == 22 );
	assert( s14.pop() == 11 );
	assert( s14.isEmpty() );
	cout << " 7 " << flush;
      // self-assignment, non-minimal size
      s13 = s13;
	assert( !s13.isEmpty() );
	assert( s13.isFull() );
	assert( s13.pop() == 22 );
	assert( s13.pop() == 11 );
	assert( s13.isEmpty() );
	cout << " 8 " << flush;
	cout << "Passed!" << endl;
}

void StackTester::testDestructor() {
	cout << "- Testing destructor..." << flush;
	// minimal, empty
	Stack<Item> s1(1);
	s1.~Stack();
	assert( s1.isEmpty() );
	assert( s1.myArray == NULL );
	assert( s1.myCapacity == 0 );
	cout << " 1 " << flush;
	// minimal, non-empty
	Stack<Item> s2(1);
	s2.push(11);
	s2.~Stack();
	assert( s2.isEmpty() );
	assert( s2.myArray == NULL );
	assert( s2.myCapacity == 0 );
	cout << " 2 " << flush;
	// non-minimal, empty
	Stack<Item> s3(3);
	s3.~Stack();
	assert( s3.isEmpty() );
	assert( s3.myArray == NULL );
	assert( s3.myCapacity == 0 );
	cout << " 3 " << flush;
	// non-minimal, non-empty
	Stack<Item> s4(3);
	s4.push(11);
	s4.push(22);
	s4.push(33);
	s4.~Stack();
	assert( s4.isEmpty() );
	assert( s4.myArray == NULL );
	assert( s4.myCapacity == 0 );
	cout << " 4 " << flush;
	cout << " Passed!" << endl;
}



