/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student Name: Landon Sterk
 * Date: March 3 2015
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef PROJECT4_MATRIX_H_
#define PROJECT4_MATRIX_H_

#include "Vec.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

//typedef double Item;

template<class Item>
class Matrix {
public:
	Matrix(); //default constructor
	Matrix(unsigned rows, unsigned columns);//explicit value constructor
	Vec<Item>& operator[](unsigned index);//write subscript operator
	const Vec<Item>& operator[](unsigned index) const;//read subscript operator
	bool operator==(const Matrix& m2) const;//equality operator
	unsigned getRows()const ;//row size accessor
	unsigned getColumns()const ;//column size accessor


	//Methods written by Landon
	bool operator!=(const Matrix& m2) const;//inequality operator
	void readFrom(istream& input);
	Matrix operator+(const Matrix& m2); //addition operator
	void writeTo(string target); //write to an explicit file name

	//Methods written by Nate
	Matrix operator-(const Matrix& m2); //subtraction operator
	void writeTo(ostream& out); //write a matrix to a stream
	void readFrom(string filename); //read a matrix from a file into a stream
	Matrix getTranspose(); // Swaps the rows and columns of a matrix, and returns the new matrix



private:
	unsigned myRows;//number of rows in the matrix
	unsigned myColumns;//number of columns in the matrix
	Vec< Vec<Item> > myVec;//Vector of vectors = matrix
	friend class MatrixTester;//gives tester class access to private values
};

template<class Item>
Matrix<Item>::Matrix(){
	/*
	 * Default constructor for class Matrix
	 * initializes myRows and myColumns to 0
	 */
	myRows = myColumns = 0;
}

template<class Item>
Matrix<Item>::Matrix(unsigned rows, unsigned columns){
	/*
	 * Explicit value constructor
	 * @param unsigned rows, unsigned columns
	 * Initializes myRows to rows, myColumns to columns
	 * Sets the size of matrix to myRows x myColumns
	 */
	myRows = rows;
	myColumns = columns;
	myVec.setSize(myRows);
	for(unsigned i = 0; i < myRows; i++){
		myVec[i].setSize(myColumns);
	}
}

template<class Item>
Vec<Item>& Matrix<Item>::operator[](unsigned index){
	/*
	 * Subscript operator for Matrix that allows full access
	 * @param unsigned index
	 * @returns Vec<item>, a Vec (row) of the matrix,
	 * Precondition: index must be less than the number of rows
	 */
	if(index >= myRows)throw range_error("Invalid subscript");
	return myVec[index];
}

template<class Item>
const Vec<Item>& Matrix<Item>::operator[](unsigned index)const{
	/*
	 * Subscript operator for Matrix w/ read only access
	 * @param unsigned index
	 * @returns Vec<item>, a READ ONLY Vec (row) of the matrix
	 * Precondition: index must be less than the number of rows
	 */
	if(index >= myRows)throw range_error("Invalid subscript");
	return myVec[index];
}

template<class Item>
bool Matrix<Item>::operator==(const Matrix& m2) const{
	/*
	 * Equality operator for Matrix
	 * @param read-only reference to Matrix m2
	 * @return bool, whether or not the matrices are equal
	 * Note: contents of the matrices must be the equal, but not necessarily same location
	 */
	if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
		return false;
	} else {
		return myVec == m2.myVec;
	}
}

template<class Item>
bool Matrix<Item>::operator!=(const Matrix& m2) const{
	/*
	 * Inequality operator for Matrix
	 * Written by Landon
	 * @param read-only reference to Matrix m2
	 * @return bool, whether or not the matrices are Inequal
	 * Note: if dimensions OR any one value of the matrix are different, returns false
	 */
	return not(* this == m2);
}

template<class Item>
unsigned Matrix<Item>::getRows() const {
	/*
	 * Accessor method for myRows
	 * @param none
	 * @return unsigned myRows, the number of rows in the Matrix
	 */
	return myRows;
}

template<class Item>
unsigned Matrix<Item>::getColumns() const {
	/*
	 * Accessor method for myColumns
	 * @param none
	 * @return unsigned myColumns, the number of columns in the Matrix
	 */
	return myColumns;
}

template<class Item>
Matrix<Item> Matrix<Item>::getTranspose() {
	/*
	 * Accessor method for the transposed version of a matrix
	 * @param none
	 * @return Matrix inverse, the original matrix with rows and columns switched
	 */
	Matrix<Item> inv(myColumns, myRows);
	for(unsigned i = 0; i < myColumns; i++){
		for(unsigned j = 0; j < myRows; j++){
			inv[i][j] = myVec[j][i];
		}
	}
	return inv;
}

template<class Item>
void Matrix<Item>::readFrom(istream& input){
	/*
	 * Method that populates a matrix with predefined dimensions with values from input stream
	 * Written by Landon
	 * @param istream input , the source of values for the matrix
	 * Note: inputs are assumed to be in a format of spaces between items in a row, and \n between rows
	 */
	string blankline;
	for(unsigned i = 0; i < myRows; i++){
		getline(input, blankline);
		for(unsigned j = 0; j < myColumns; j++){
			input >> myVec[i][j];
		}
	}
}

template<class Item>
void Matrix<Item>::writeTo(ostream& out){
	/*
	 * Method that outputs a pre-existing matrix into an output stream
	 * Written by Nate
	 * @param outstream output , the destination of values of the matrix
	 */
	for(unsigned i = 0; i < myRows; i++){
		for(unsigned j = 0; j < myColumns; j++){
			out << myVec[i][j] << ' ';
		}
		out << '\n';
	}
}

template<class Item>
void Matrix<Item>::readFrom(string filename){
	/*
	 * Reads from a file given a path name
	 * Written by Nate
	 * @param string filename, the name of the file in the local directory from which the matrix will be read
	 */
	ifstream fin(filename.c_str());
	fin >> myRows;
	fin >> myColumns;
	myVec.setSize(myRows);
	for(unsigned i = 0; i < myRows; i++){
		myVec[i].setSize(myColumns);
	}

	for(unsigned i = 0 ;i < myRows; i++){
		for(unsigned j = 0; j < myColumns; j++){
			fin >> myVec[i][j];
		}
	}
	fin.close();
}

template<class Item>
void Matrix<Item>::writeTo(string target){

	/*
	 * Writes to a file given a path name
	 * Written by Landon
	 * @param string target, the name of the file in the local directory to which the matrix will be written
	 * Note: a writeTo(ostream& out) method MUST BE WRITTEN for this to work!
	 * Note: testing for this method also requires readFrom(string target) to work!
	 */
	fstream fout(target.c_str());
	fout << myRows << ' ' << myColumns << endl;
	writeTo(fout);
}

template<class Item>
Matrix<Item> Matrix<Item>::operator+(const Matrix& m2){
	/*
	 * Addition operator for two Matrices of identical size
	 * Written by Landon
	 * @param const read-only reference Matrix m2
	 * @return Matrix matSum , the sum of the two matrices
	 * Preconditions: the two matrices must have identical dimensions
	 */
	if(myRows != m2.myRows)throw invalid_argument("Matrices must have same number of rows for addition to be defined");
	if(myColumns != m2.myColumns)throw invalid_argument("Matrices must have same number of columns for addition to be defined");
	Matrix<Item> matSum(myRows, myColumns);
	for(unsigned i = 0; i < myRows; i++){
		for(unsigned j = 0; j < myColumns; j++){
			matSum[i][j] = myVec[i][j] + m2[i][j];
		}
	}
	return matSum;
}

template<class Item>
Matrix<Item> Matrix<Item>::operator-(const Matrix& m2){
	/*
	 * Subtraction operator for two Matrices of identical size
	 * Written by Nate Bender
	 * @param const read-only reference Matrix m2
	 * @return Matrix matDifference , the difference of the two matrices
	 * Preconditions: the two matrices must have identical dimensions
	 */
	if(myRows != m2.myRows)throw invalid_argument("Matrices must have same number of rows for subtraction to be defined");
	if(myColumns != m2.myColumns)throw invalid_argument("Matrices must have same number of columns for subtraction to be defined");
	Matrix<Item> matDifference(myRows, myColumns);
	for(unsigned i = 0; i < myRows; i++){
		for(unsigned j = 0; j < myColumns; j++){
			matDifference[i][j] = myVec[i][j] - m2[i][j];
		}
	}
	return matDifference;
}


#endif
