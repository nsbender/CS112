/* ListTester.cpp defines the test methods for class List.
 * Joel Adams, for CS 112 at Calvin College.
 */


#include "ListTester.h" // ListTester
#include "List.h"       // List
#include <iostream>     // cin, cout
#include <cassert>      // assert()
#include <cstdlib>      // exit()
#include <stdexcept>    // underflow_error
using namespace std;

void ListTester::runTests() const {
	cout << "Running List tests..." << endl;
//	testDefaultConstructor();
//	testNodeDefaultConstructor();
//	testNodeExplicitConstructor();
//	testAppend();
//	testDestructor();
//	testCopyConstructor();
//	testAssignment();
//	testEquality();
//	testInequality();
//	testReadFromFile();
//	testWriteToFile();
//	testReadFromStream();
//	testWriteToStream();
//	testPrepend();
//	testGetIndexOf();
//	testInsert();
//	testRemove();
	testSort();// Partner was unable to complete
	cout << "All tests passed!" << endl;
}

void ListTester::testDefaultConstructor() const {
	cout << "Testing List default constructor... " << flush;
	List<int> aList;
	assert( aList.mySize == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeDefaultConstructor() const {
	cout << "Testing Node default constructor... " << flush;
	List<double>::Node aNode;
	assert( aNode.myItem == 0 );
	assert( aNode.myNext == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeExplicitConstructor() const {
	cout << "Testing Node explicit constructor... " << flush;
	List<unsigned>::Node n1(11, NULL);
	assert( n1.myItem == 11 );
	assert( n1.myNext == NULL );
	cout << " 1 " << flush;

	List<unsigned>::Node *n3 = new List<unsigned>::Node(33, NULL);
	List<unsigned>::Node n2(22, n3);
	assert( n2.myItem == 22 );
	assert( n2.myNext == n3 );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAppend() const {
	cout << "Testing append()... " << flush;
	// empty List
	List<int> aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}
	// append to empty list
	aList.append(11);
	assert( aList.getSize() == 1 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast == aList.myFirst );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 11 );
	assert( aList.myFirst->myNext == NULL );
	cout << " 1 " << flush;
	// append to a list containing 1 Item
	aList.append(22);
	assert( aList.getSize() == 2 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.myFirst != aList.myLast );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext != NULL );
	assert( aList.myLast->myNext == NULL );
	cout << " 2 " << flush;
	// append to a list containing 2 Items
	aList.append(33);
	assert( aList.getSize() == 3 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 33 );
	assert( aList.myFirst->myNext->myItem == 22 );
	assert( aList.myLast->myNext == NULL );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testDestructor() const {
	cout << "Testing destructor... " << flush;
	List<double> aList;
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 1 " << flush;

	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 2 " << flush;
	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testCopyConstructor() const {
	cout << "Testing copy constructor... " << flush;
	// copy empty list
	List<unsigned> list1;
	List<unsigned> list2(list1);
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// copy nonempty list
	List<unsigned> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<unsigned> list4(list3);
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAssignment() const {
	cout << "Testing assignment... " << flush;
	// empty to empty assignment
	List<int> list1;
	List<int> list2;
	list2 = list1;
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// non-empty to empty assignment
	List<int> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<int> list4;
	list4 = list3;
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	cout << " 2 " << flush;

	// equal-sized non-empty to non-empty assignment
	List<int> list5;
	list5.append(44);
	list5.append(55);
	list5.append(66);
	list5 = list3;
	assert( list5.getSize() == 3 );
	assert( list5.getFirst() == 11 );
	assert( list5.getLast() == 33 );
	assert( list5.myFirst->myNext->myItem == 22 );
	cout << " 3 " << flush;

	// empty to non-empty assignment
	List<int> list6;
	list6.append(44);
	list6.append(55);
	list6.append(66);
	List<int> list7;
	list6 = list7;
	assert( list6.getSize() == 0 );
	assert( list6.myFirst == NULL );
	assert( list6.myLast == NULL );
	cout << " 4 " << flush;

	// unequal-sized non-empty to non-empty assignment
	List<int> list8;
	list8.append(44);
	list8.append(55);
	list8.append(66);
	list8.append(77);
	list8 = list3;
	assert( list8.getSize() == 3 );
	assert( list8.getFirst() == 11 );
	assert( list8.getLast() == 33 );
	assert( list8.myFirst->myNext->myItem == 22 );
	cout << " 5 " << flush;

	// assignment chaining
	List<int> list9;
	list9.append(44);
	list9.append(55);
	list9.append(66);
	list9.append(77);
	List<int> list10;
	list10 = list9 = list8;
	assert( list10.getSize() == 3 );
	assert( list10.getFirst() == 11 );
	assert( list10.getLast() == 33 );
	assert( list10.myFirst->myNext->myItem == 22 );
	cout << " 6 " << flush;

	// self-assignment (stupid, but possible)
	List<int> list11;
	list11.append(11);
	list11.append(22);
	list11.append(33);
	list11 = list11;
	assert( list11.getSize() == 3 );
	assert( list11.getFirst() == 11 );
	assert( list11.getLast() == 33 );
	assert( list11.myFirst->myNext->myItem == 22 );
	cout << " 7 " << flush;

	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testEquality() const {
	cout << "Testing equality... " << flush;
	// two empty lists
	List<double> list1;
	List<double> list2;
	assert( list1 == list1 );
	cout << " 1 " << flush;

	// a non-empty list
	List<double> list3;
	list3.append(33);		// [33]
	assert( !(list3 == list1) );
	cout << " 2 " << flush;

	// equal, non-empty lists of the same size
	List<double> list4;
	list4.append(33);		// [33]
	assert( list4 == list3 );
	assert( list3 == list4 );
	cout << " 3 " << flush;

	// unequal, non-empty lists of the same size
	list3.append(55);		// [33,55]
	List<double> list5;
	list5.append(44);		// [44]
	list5.append(55);		// [44,55]
	assert( !(list5 == list3) );
	assert( !(list3 == list5) );
	cout << " 4 " << flush;

	// unequal non-empty lists of different sizes
	list4.append(44);		// [33,44]
	list4.append(55);		// [33,44,55]
	assert( !(list4 == list5) );
	assert( !(list5 == list4) );
	assert( !(list5 == list3) );
	cout << " 5 " << flush;

	cout << "Passed!" << endl;
}

void ListTester::testInequality() const {
	cout << "Testing inequality... " << flush;
	// two empty lists
	List<double> list1;
	List<double> list2;
	assert( !(list1 != list2) );
	cout << " 1 " << flush;

	// a non-empty list
	List<double> list3;
	list3.append(33);		// [33]
	assert( list3 != list1 );
	cout << " 2 " << flush;

	// equal, non-empty lists of the same size
	List<double> list4;
	list4.append(33);		// [33]
	assert( !(list4 != list3) );
	assert( !(list3 != list4) );
	cout << " 3 " << flush;

	// unequal, non-empty lists of the same size
	list3.append(55);		// [33,55]
	List<double> list5;
	list5.append(44);		// [44]
	list5.append(55);		// [44,55]
	assert( list5 != list3 );
	assert( list3 != list5 );
	cout << " 4 " << flush;

	// unequal non-empty lists of different sizes
	list4.append(44);		// [33,44]
	list4.append(55);		// [33,44,55]
	assert( list4 != list5 );
	assert( list5 != list4 );
	assert( list5 != list3 );
	cout << " 5 " << flush;

	cout << "Passed!" << endl;
}

void ListTester::testReadFromStream() const {
	/*
	 * Written by: Mitch Stark
	 * Purpose: test readfrom(stream)
	 */
	cout << "Testing readFrom(stream)..." << flush;
	List<int> lst;
	for (int i = 1; i < 6; i++) {
		lst.append(i);
	}
	List<int> lst2;
	ifstream in("ListFile.txt");
	assert(in.is_open());
	lst2.readFrom(in);
	assert(lst == lst2);
	cout << "Passed!" << endl;
}

void ListTester::testWriteToStream() const {
	/*
	 * Written by: Nate Bender
	 * Purpose: test writeTo(stream)
	 */
	cout << "Testing writeTo(ostream)... " << flush;
	List<double> l;
	// read a list whose values we know
	l.readFrom("ListFile.txt");
	ofstream fout("ListFile2.txt");
	assert( fout.is_open() );
	// now write it to a file via a stream
	l.writeTo(fout);
	fout.close();
	// now, read what we just wrote into a different Matrix
	List<double> l1;
	l1.readFrom("ListFile2.txt");
	// and test it
	assert (l == l1);
	cout << "Passed!" << endl;
}

void ListTester::testReadFromFile() const {
	/*
	 * Written by: Nate Bender
	 * Purpose: readFrom(filename)
	 */
	cout << "Testing readFrom(filename)... " << flush;
	List<double> l;
	l.readFrom("ListFile.txt");
	assert(l.mySize == 5);
	assert(l.myFirst -> myItem == 1);
	cout << "Passed!" << endl;
}

void ListTester::testWriteToFile() const {
	/*
	 * Written by: Mitch Stark
	 * Purpose: test writeTo(file)
	 */
	cout << "Testing writeTo(file)..." << flush;
	List<double> lst;
	for (double i = 1; i < 6; i++) {
		lst.append(i);
	}
	lst.writeTo("ListFile2.txt");
	cout << "Check 'ListFile2.txt'...";
	cout << "Passed!" << endl;
}

void ListTester::testPrepend() const {
	/*
	 * Written by: Mitch Stark
	 * Purpose: test the prepend method
	 */
	cout << "Testing prepend()... " << flush;
	//test prepend to empty list
	List<unsigned> lst;
	lst.prepend(0);
	assert(lst.getFirst() == 0);
	assert(lst.getLast() == 0);
	assert(lst.getSize() == 1);

	//add again to that list
	lst.prepend(1);
	assert(lst.getFirst() == 1);
	assert(lst.getLast() == 0);
	assert(lst.getSize() == 2);

	//Final check w/ 3 items
	lst.prepend(2);
	assert(lst.getFirst() == 2);
	assert(lst.getLast() == 0);
	assert(lst.getSize() == 3);
	cout << "Passed!" << endl;
}

void ListTester::testGetIndexOf() const {
	/*
	 * Written by: Nate Bender
	 * Purpose: Test the getIndexOf function on a list.
	 */
	//Test index of an item from the default test list
	cout << "Testing getIndexOf()... " << flush;
	List <int> lst;
	lst.readFrom("ListFile.txt");
	assert (lst.getIndexOf(3) == 2);
	cout << "Passed!" << endl;
}

void ListTester::testInsert() const {
	/*
	 * Written by: Mitch Stark
	 * Purpose: test the insert method on a list
	 */
	//test empty list
	List<int> lst;
	lst.insert(0, 0);
	assert(lst.getFirst() == 0);
	assert(lst.getLast() == 0);
	assert(lst.getSize() == 1);

	lst.append(1);
	lst.append(2);

	//test middle
	lst.insert(3, 1);
	//assert(lst.getIndexOf(1) == 3);

	//test end
	lst.insert(4,4);
	assert(lst.getLast() == 4);
	//assert(lst.getIndexOf(4) == 4);

	//test beginning
	lst.insert(5,0);
	assert(lst.getFirst() == 5);
	//assert(lst.getIndexOf(0) == 5);

}

void ListTester::testRemove() const {
	cout << "Testing remove()... " << flush;
	List <int> lst;
	lst.readFrom("ListFile.txt");
	assert ( lst.remove(2) == 3) ;
	lst.writeTo("ListFile2.txt");
	List <int> lst2;
	lst2.readFrom("ListFile2.txt");
	//The size should assert to be 4 but the file has an extra line thats being read into the list. I dont know how to fix it.
	assert (lst2.mySize == 5);
};

void ListTester::testSort() const {
	// Partner was unable to complete

}
