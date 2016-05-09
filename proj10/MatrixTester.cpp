/* MatrixTester.cpp tests Matrix operations.
 * Author: Joel C. Adams, for CS 112 at Calvin College.
 * Copyright 2009, Joel C. Adams.  All rights reserved.
 */

#include "MatrixTester.h"

void MatrixTester::runTests() {
	cout << "Testing class Matrix." << endl;
	testConstructor();
	testEquality();
	testCopyConstructor();
	testAssignment();
        testAddition();
	testTranspose();
	cout << "All tests passed!" << endl;
}


void MatrixTester::testAddition() {
	cout << "- testing operator+ ... " << flush;
	Matrix m1, m2;
	m1.fill("testFiles/4096x4096.txt");
	m2.fill("testFiles/4096x4096.txt");
	Matrix m3 = m1 + m2;
	assert( m3.getRows() == m1.getRows() );
	assert( m3.getColumns() == m1.getColumns() );
	for (unsigned i = 0; i < m3.getRows(); i++) {
		for (unsigned j = 0; j < m3.getColumns(); j++) {
			assert( m3[i][j] == 2*(i*m3.getRows()+j) );
		}
	}
	cout << " 1 " << flush;
	Matrix m4;
	try {
		Matrix m5 = m4 + m3;
	} catch ( invalid_argument& ) {
		cout << " 2 " << flush;
	}
	cout << " Passed!" << endl;
}

void MatrixTester::testTranspose() {
	cout << "- testing transpose()... " << flush;
	// empty case
	Matrix m0;
	try {
		m0.transpose();
	} catch ( invalid_argument& ) {
		cout << " 0 " << flush;
	}
	// nonempty
	Matrix m2(3, 4);
	for (unsigned i = 0; i < 3; i++) {
		for (unsigned j = 0; j < 4; j++) {
			m2[i][j] = i+j+10;
		}
	}
	Matrix m1 = m2.transpose();
	assert(m1.getRows() == 4);
	assert( m1.getColumns() == 3);
	cout << " 1a " << flush;
	for (unsigned r = 0; r < 4; r++) {
		for (unsigned c = 0; c < 3; c++) {
			assert( m1[r][c] == r+c+10 );
		}
	}
	cout << " 1b " << flush;
	assert( m1.myMatrix != m2.myMatrix );
	cout << " 1c " << flush;

	cout << " Passed!" << endl;
}

void MatrixTester::testAssignment() {
	cout << "- assignment... " << flush;
	// empty
	Matrix m0;
	Matrix m1;
	m1 = m0;
	assert( m1.getRows() == 0 );
	assert( m1.getColumns() == 0 );
	assert( m1.myMatrix == NULL );
	cout << " 0 " << flush;
	// nonempty to empty
	Matrix m2(3, 4);
	for (unsigned i = 0; i < 3; i++) {
		for (unsigned j = 0; j < 4; j++) {
			m2[i][j] = i+j+10;
		}
	}
	m1 = m2;
	assert(m1.getRows() == 3);
	assert( m1.getColumns() == 4);
	cout << " 1a " << flush;
	for (unsigned r = 0; r < 3; r++) {
		for (unsigned c = 0; c < 4; c++) {
			assert( m1[r][c]== r+c+10 );
		}
	}
	cout << " 1b " << flush;
	assert( m1.myMatrix != m2.myMatrix );
	cout << " 1c " << flush;
	// empty to nonempty
	m1 = m0;
	assert( m1.getRows() == 0 );
	assert( m1.getColumns() == 0 );
	assert( m1.myMatrix == NULL );
	cout << " 2 " << flush;
	// nonempty to nonempty
	Matrix m3(2,2);
	m3 = m2;
	assert(m3.getRows() == 3);
	assert( m3.getColumns() == 4);
	cout << " 3a " << flush;
	for (unsigned r = 0; r < 3; r++) {
		for (unsigned c = 0; c < 4; c++) {
			assert( m3[r][c] == r+c+10 );
		}
	}
	cout << " 3b " << flush;
	assert( m3.myMatrix != m2.myMatrix );
	cout << " 3c " << flush;
	// chaining
	m3 = m0 = m2;
	assert(m3.getRows() == 3);
	assert( m3.getColumns() == 4);
	cout << " 4a " << flush;
	for (unsigned r = 0; r < 3; r++) {
		for (unsigned c = 0; c < 4; c++) {
			assert( m3[r][c] == r+c+10 );
		}
	}
	cout << " 4b " << flush;
	assert( m3.myMatrix != m2.myMatrix );
	assert( m3.myMatrix != m0.myMatrix );
	assert( m0.myMatrix != m2.myMatrix );
	cout << " 4c " << flush;
	// self-assignment
	m3 = m3;
	assert(m3.getRows() == 3);
	assert( m3.getColumns() == 4);
	cout << " 5a " << flush;
	for (unsigned r = 0; r < 3; r++) {
		for (unsigned c = 0; c < 4; c++) {
			assert( m3[r][c] == r+c+10 );
		}
	}
	cout << " 5b " << flush;

	cout << " Passed! " << endl;
}

void MatrixTester::testCopyConstructor() {
	cout << "- copy constructor... " << flush;
	// empty case
	Matrix m0;
	Matrix m1(m0);
	assert( m1.getRows() == 0 );
	assert( m1.getColumns() == 0 );
	assert( m1.myMatrix == NULL );
	cout << " 0 " << flush;
	// nonempty
	Matrix m2(3, 4);
	for (unsigned i = 0; i < 3; i++) {
		for (unsigned j = 0; j < 4; j++) {
			m2[i][j] = i+j+10;
		}
	}
	Matrix m3(m2);
	assert(m3.getRows() == 3);
	assert( m3.getColumns() == 4);
	cout << " 1a " << flush;
	for (unsigned r = 0; r < 3; r++) {
		for (unsigned c = 0; c < 4; c++) {
			assert( m3[r][c] == r+c+10 );
		}
	}
	cout << " 1b " << flush;
	assert( m3.myMatrix != m2.myMatrix );
	cout << " 1c " << flush;
	cout << " Passed! " << endl;
}


void MatrixTester::testEquality() {
	cout << "- equality... " << flush;
	// empty case
	Matrix m0, m1;
	assert( m0 == m1 );
	cout << " 0 " << flush;
	// non-empty but equal case
	Matrix m2, m3;
	m2.fill("testFiles/mat1.txt");
	m3.fill("testFiles/mat1.txt");
	assert( m2 == m3 );
	cout << " 1 " << flush;
	// nonempty, same size, not equal at first item
	Matrix m4;
	m4.fill("testFiles/mat2.txt");
	assert( !(m2 == m4) );
	cout << " 2a " << flush;
	// nonempty, same size, not equal at last item
	Matrix m5;
	m5.fill("testFiles/mat3.txt");
	assert( !(m2 == m5) );
	cout << " 2b " << flush;
	// nonempty, same size, not equal at interior item
	Matrix m6;
	m6.fill("testFiles/mat4.txt");
	assert( !(m2 == m6) );
	cout << " 2c " << flush;
	// nonempty, different rows
	Matrix m7;
	m7.fill("testFiles/mat5.txt");
	assert( !(m2 == m7) );
	cout << " 3a " << flush;
	// nonempty, different columns
	Matrix m8;
	m8.fill("testFiles/mat6.txt");
	assert( !(m2 == m8) );
	cout << " 3b " << flush;

	cout << "Passed!" << endl;
}

void MatrixTester::testConstructor() {
	cout << "- constructor... " << flush;
	Matrix m0;
	assert( m0.getRows() == 0 );
	assert( m0.getColumns() == 0 );
	cout << " 0 " << flush;
	Matrix m1(3, 4);
	assert( m1.getRows() == 3 );
	assert( m1.getColumns() == 4 );
	cout << " 1a " << flush;
	for (unsigned i = 0; i < 3; i++) {
		for (unsigned j = 0; j < 4; j++) {
			assert( m1[i][j] == 0 );
		}
	}
	cout << " 1b " << flush;

	cout << " Passed!" << endl;
}

