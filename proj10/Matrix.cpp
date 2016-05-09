/* Matrix.cpp defines non-trivial Matrix operations.
 * Author: Joel C. Adams, for CS 112 at Calvin College.
 * Copyright 2009, Joel C. Adams.  All rights reserved.
 */

#include "Matrix.h"

/* --- copy constructor
 * Parameters: original, a Matrix
 * Postcondition: I am a distinct copy of original.
 */
Matrix::Matrix(const Matrix& original) {
	makeCopyOf(original);
}

/* --- utility method refactored from copy constructor and operator=
 * Parameters: original, a Matrix
 * Postcondition: I am a distinct copy of original.
 */
void Matrix::makeCopyOf(const Matrix& original) {
	myRows = myColumns = 0;
	myMatrix = NULL;
	if (original.getRows() != 0) {
		unsigned r = original.getRows();
		unsigned c = original.getColumns();
		allocate(r, c );
		unsigned size = r*c;
		for (unsigned i = 0; i < size; i++) {
			myMatrix[i] = original.myMatrix[i];
		}
		myRows = r;
		myColumns = c;
	}
}

/* --- utility to allocate space dynamically
 * Parameters: rows and columns, two unsigned ints.
 * Precondition: rows > 0 && columns > 0.
 * Postcondition: myMatrix points to a rows x columns block of memory.
 */
void Matrix::allocate(unsigned rows, unsigned columns) {
	// avoid memory leak
	if (myMatrix != NULL) {
		deallocate();
	}
	// allocate block of memory
	myMatrix = new Item[rows*columns];
}

/* --- utility to deallocate my storage, refactored from
 *      destructor, operator=, and other destructive methods.
 * Postcondition: my storage has been returned to the heap &&
 *                 myMatrix == NULL && myRows == 0 && myColumns == 0.
 */
void Matrix::deallocate() {
	// delete the array of Items
	delete [] myMatrix;
	// clean up
	myMatrix = NULL;
	myRows = myColumns = 0;
}

/* --- initialize the Matrix's elements to a common value
 * Parameter: value, an Item.
 * Postcondition: all elements in myMatrix == value.
 */

void Matrix::initialize(Item value) {
	unsigned size = myRows * myColumns;
	for (unsigned i = 0; i < size; i++) {
		myMatrix[i] = value;
	}
}


/* assignment
 * Parameters: original, another Matrix.
 * Postcondition: I am a copy of original && 
 *                 I have not leaked any memory.
 */
Matrix& Matrix::operator=(const Matrix& original) {
	if (this != &original) {
		if (myRows > 0) {
			deallocate();
		}
		makeCopyOf(original);
	}
	return *this;
}

/* addition
 * Parameters: mat2, another Matrix.
 * Precondition: mat2.getRows() == myRows &&
 *               mat2.getColumns() == myColumns.
 * Return: result, a Matrix with my dimensions
 *          containing the sum of myself and mat2.
 */
Matrix Matrix::operator+(const Matrix& mat2) const {
	if (myRows != mat2.getRows() || myColumns != mat2.getColumns() ) {
		throw invalid_argument("Matrix::operator+: matrix dimensions mismatch");
	}
	Matrix result(myRows, myColumns);
	#pragma omp parallel
	{
		unsigned threadID = omp_get_thread_num();
		unsigned numThreads = omp_get_num_threads();
		for (unsigned rows = threadID; rows < myRows; rows += numThreads) {
			for (unsigned cols = 0; cols < myColumns; cols++) {
				result[rows][cols] = (*this)[rows][cols] + mat2[rows][cols] ;
			}
		}
	}
	return result;
}


/* transpose
 * Return: result, containing a myColumns-by-myRows Matrix,
 *                whose column values are my row values
 */
Matrix Matrix::transpose() const {
	if (myRows <= 0) {
		throw invalid_argument("Matrix::transpose(): empty Matrix!");
	}
	Matrix result(myColumns, myRows);
	#pragma omp parallel
	{
		unsigned threadID = omp_get_thread_num();
		unsigned numThreads = omp_get_num_threads();
		for (unsigned rows = threadID; rows < myRows; rows += numThreads) {
			for (unsigned cols = 0; cols < myColumns; cols++) {
				result[cols][rows] = (*this)[rows][cols];
			}
		}
	}
	return result;
}

/* --- output using *this
 * Parameter: out, an ostream.
 * Precondition: out is an open ostream
 * Postcondition: my values have been inserted into out,
 *                 with tab chars between each value.
 */
void Matrix::print(ostream& out) const {
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			out << (*this)[i][j] << '\t';
		}
		out << '\n';
	}
}

/* --- input using *this
 * Parameter: in, an ostream.
 * Precondition: in is an open istream
 *                containing myRows x myColumns values.
 * Post condition: I now contain a copy of the values from in.
 */
void Matrix::read(istream& in) {
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			in >> (*this)[i][j];
		}
	}
}

/* --- input from file
 * Parameter: fileName, a string.
 * Precondition: fileName is the name of (or path to) a file,
 *                 the first line of file is #rows #columns,
 *                 and the remainder of which is rows x columns values.
 * Postcondition: myRows == rows && myColumns == columns &&
 *                 I contain the other values from fileName.
 */
void Matrix::fill(const string& fileName) {
	ifstream fin( fileName.c_str() );
	assert ( fin.is_open() );
	unsigned rows, columns;
	fin >> rows >> columns;
	assert (rows > 0 && columns > 0);
	myRows = rows; myColumns = columns;
	allocate(rows, columns);
	Item value;
	#pragma omp parallel for schedule(dynamic , 1)
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < columns; j++) {
			fin >> value;
			assert( !fin.eof() );
			(*this)[i][j] = value;
		}
	}
	fin.close();
}

/* --- output to a file
 * Parameter: fileName, a String.
 * Postcondition: the file named fileName contains myRows and myColumns on the first line,
 *                and each subsequent line contains one of my rows.
 */
void Matrix::dump(const string& fileName) {
	ofstream fout( fileName.c_str() );
	assert( fout.is_open() );
	fout << myRows << ' ' << myColumns << '\n';
	this->print(fout);
	fout.close();
}



/* --- boolean equality
 * Parameter: mat2, a Matrix.
 * Postcondition: true is returned, if and only if
 *                 myRows == mat2.rows() &&
 *                 myColumns == mat2.columns() &&
 *                 my values are the same as mat2's values.
 */
bool Matrix::operator ==(const Matrix& mat2) const {
	if (myColumns != mat2.getColumns() || myRows != mat2.getRows() ) {
		return false;
	}
	for (unsigned i = 0; i < mat2.getRows(); i++) {
		for (unsigned j = 0; j < mat2.getColumns(); j++) {
			if ( (*this)[i][j] != mat2[i][j] )  {
				return false;
			}
		}
	}
	return true;
}


/* --- multiplication
 * Parameters: mat2, a Matrix.
 * Precondition: myColumns == mat2.rows().
 * Postcondition: a Matrix is returned containing the product of
 *                 my values and those of mat2.
 */
Matrix Matrix::operator*(const Matrix& mat2) const
{
	if (myColumns != mat2.getRows()){               // check dimensions
		throw invalid_argument("Matrix::operator*(): invalid dimensions");
	}

	Matrix mat3(myRows, mat2.getColumns());             // build result Matrix

	#pragma omp parallel for schedule(dynamic,2 )
	for (unsigned i = 0; i < myRows; i++)               // for each of my rows:
		for (unsigned j = 0; j < mat2.getColumns(); j++)  //  for each col in mat2:
		{
			double sum = 0;
			for (unsigned k = 0; k < myColumns; k++)       //   for each of my columns:
				sum += (*this)[i][k] * mat2[k][j];          //     sum the products
			mat3[i][j] = sum;                           //     put sum in result
		}
	return mat3;                                        // return result matrix
}

