/* Vec.h provides a simple vector class named Vec.
 * Student Name: Landon Sterk
 * Date: February 24, 2015
 * CS 112 Lab 03
 * Begun by: Joel C. Adams, for CS 112 at Calvin College. Edited and expanded by Landon Sterk
 */

#ifndef PROJECT4_VEC_H_
#define PROJECT4_VEC_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <math.h> // Used in finding the middle item in a Vec
using namespace std;

template<class Item>
class Vec {
public:
	Vec(); //default constructor
	Vec(unsigned size); //explicit value constructor
	virtual ~Vec(); //destructor
	Vec(const Vec<Item>& original); //copy constructor
	Vec<Item>& operator=(const Vec<Item>& original); //assignment operator
	unsigned getSize(); //accessor for mySize
	void setItem(unsigned index, const Item& it); //sets item at index index to value it
	Item getItem(unsigned index) const; // accessor for item at index index in myArray
	void setSize(unsigned newSize); // changes the size of the array to newSize
	bool operator==(const Vec<Item>& v2) const; // equality operator
	void writeTo(ostream& out) const; // output to stream
	void readFrom(istream& in); //input values
	bool operator!=(const Vec<Item>& other) const; //inequality operator
	Vec operator-(const Vec<Item>& other); //subtraction operator between two arrays
	void readFrom(const string& filename); //reads values into this.myArray from filename.txt
	const Item& operator[] (unsigned index) const;
	void writeTo(string fileName); //writes values from this.myArray to filename.txt
	Item& operator[] (unsigned index); // returns location of an item at the specified index
	Vec operator+(const Vec<Item>& v2); // addition operator for two Vecs
	double operator*(const Vec<Item>& v2); // dot multiplication operator for two Vecs
	Vec sort(Vec& inputVec); // Use the merge sort function on a given vector
	Vec& merge(Vec &input, Vec firstHalf, Vec secondHalf); // Recombine and sort two vectors that have had sort() used on them
private:
	unsigned mySize; //object variable that tracks the size of the array
	Item * myArray; //array object variable
	friend class VecTester; //permits the VecTester class to access private values of Vec objects
};

// Method Defintions
template<class Item>
Vec<Item>::Vec() {
	/*
	 * Default constructor for Vec
	 * @param : none
	 * Initializes a null array with a size of 0
	 */
	myArray = NULL;
	mySize = 0;
}

template<class Item>
Vec<Item>::Vec(unsigned size) {
	/*
	 * Explicit value constructor for Vec
	 * @param : unsigned size, which is the number of values to be stored in the array
	 * Initializes an array of length 'size', where each value is 0
	 * Preconditions: size must be an integer >= 0.
	 * Note that if size == 0, the Array will have a location BUT not any components
	 */
	mySize = size;
	myArray = new Item[mySize];
	for(unsigned i = 0; i < mySize; i++){
		myArray[i] = 0;
	}
}

template<class Item>
Vec<Item>::~Vec() {
	/*
	 * Destructor for Vec -- deallocates the memory held by myArray, restores Vec attributes to defaults
	 * @param : none
	 */
	delete [] myArray;
	mySize = 0;
	myArray = NULL;
}

template<class Item>
Vec<Item>::Vec(const Vec& original) {
	/*
	 * Copy constructor for Vec; creates a new array that has same values but in a different location than original
	 * @param : Vec original, which is the Vec to be copied from
	 * Note: after original is used here, it can be safely changed or deleted without affecting new Vec
	 */
	mySize = original.mySize;
	if(mySize == 0) myArray = NULL;
	else {
		myArray = new Item [mySize];
		for(unsigned i = 0; i < mySize; i++){
			myArray[i] = original.myArray[i];
		}
	}
}

template<class Item>
Vec<Item>& Vec<Item>::operator=(const Vec<Item>& original) {
	/*
	 * Assignment operator for Vec
	 * @param : Vec original, which is the Vec to be copied from
	 * Note: this will deallocate a previous array for the object which is being reassigned
	 * Note: this is very similar to the copy constructor, except for it dealing with de-structing old copies
	 */
	if(this != & original){
		delete [] myArray;
		mySize = original.mySize;
		if(mySize == 0) myArray = NULL;
		else {
			myArray = new Item [mySize];
			for(unsigned i = 0; i < mySize; i++){
				myArray[i] = original.myArray[i];
			}
		}
	}
	return *this;
}

template<class Item>
unsigned Vec<Item>::getSize(){
	/*
	 * Accessor for the mySize object variable of Vec
	 * @param : none
	 * Returns this.mySize, which is an unsigned integer
	 */
	return mySize;
}

template<class Item>
void Vec<Item>::setItem(unsigned index, const Item& it){
	/*
	 * Sets the value of this.myArray[index] to a constant reference 'it'
	 * @param : unsigned index (index of target in array, const Item& it (item to be assigned to this.myArray[index]
	 * Precondition: myArray must be a valid array, and index must be within the range of 0 <= index < this.mySize
	 * Note: if index is greater than (outside of) the array, a range_error will be thrown.
	 */
	if(index >= mySize)throw range_error("no valid index");
	if(myArray != NULL and mySize > 0)myArray[index] = it;
}

template<class Item>
Item Vec<Item>::getItem(unsigned index) const{
	/*
	 * Accessor for value at this.myArray[index]
	 * @param : unsigned index, the place in the array which is to be accessed
	 * Returns: Item this.myArray[index]
	 * Preconditions: myArray must be a valid array, and index must be within the range of 0 <= index < this.mySize
	 * Note: if index is greater than (outside of) the array, a range_error will be thrown.
	 */
	if(index >= mySize)throw range_error("no valid index");
	if(myArray != NULL and 0 <= index and index < mySize)return myArray[index];
	return 0; // Return 0 if no valid index -> won't actually happen if real error occurs
}

template<class Item>
void Vec<Item>::setSize(unsigned newSize){
	/*
	 * Sets the size of a given array to a newSize, truncating or expanding as necessary
	 * @param unsigned newSize, the new length for the array
	 * Note: if newSize == the old size (this.mySize), no changes to memory are made
	 * Note: if newSize > this.mySize, the newly apportioned values will be initialized to 0
	 * Note: if newSize < this.mySize, the array will be truncated after this.myArray[newSize -1]
	 */
	if(newSize >= 0 and newSize != mySize){
		Item * temp = new Item[newSize];
		for(unsigned i = 0; i < newSize and i < mySize; i++){
			temp[i] = myArray[i];
		}
		for(unsigned i = mySize; i < newSize; i++){
			//If newSize is larger than mySize (old size), new values will be initialized to 0
			temp[i] = 0;
		}
		delete [] myArray;
		mySize = newSize;
		if(mySize > 0)myArray = temp;
		if(newSize == 0)myArray = NULL;
	}
}

template<class Item>
bool Vec<Item>::operator==(const Vec& v2) const{
	/*
	 * Equality operator for vec
	 * @param : Vec reference v2
	 * Returns: bool true if size and values stored inside this and v2 are the same, else false
	 * Note: this and v2 do NOT need to point to the same memory location to return true
	 */
	if(mySize != v2.mySize)return false;
	for(unsigned i = 0; i < mySize; i++){
		if(myArray[i] != v2.myArray[i]) return false;
	}
	return true;
}

template<class Item>
void Vec<Item>::writeTo(ostream& out) const{

	/*
	 * Writes each value of the array to a line in the file
	 * @param ostream reference out, the destination for writing the array
	 * Precondition: out must already be open for the array to be written
	 * Note: values written to the ostream will be separated by '\n'
	 */
	for(unsigned i = 0; i < mySize; i++){
		out << myArray[i] << endl;
	}
}

template<class Item>
void Vec<Item>::readFrom(istream& in){
	/*
	 * Writes each value of the array to a line in the file
	 * @param istream reference in, the location for reading the array
	 * Precondition: in must already be open for the array to be read
	 * Precondition: values read from the istream must be separated by '\n'
	 * Note: this method is compatible with the  formatting of Vec<Item>::writeTo(ostream& out)
	 */
	string blankline;
	for(unsigned i = 0; i < mySize; i++){
		in >> myArray[i];
		getline(in, blankline);
	}
}

template<class Item>
bool Vec<Item>::operator!=(const Vec& other) const{
	/*
	 * Checks to see if the two arrays have the same size and same values inside the array
	 * @param Vec read-only reference other, to be compared to implicit Vec parameter (* this)
	 * Returns the opposite of * this == other
	 * Note: this function is contingent on a Vec-specific == operator being defined to operate correctly
	 * If such an operator is not found, use the commented out text below!
	 */
	return not(* this == other);
}

template<class Item>
Vec<Item> Vec<Item>::operator-(const Vec<Item>& other){
	/*
	 * Performs subtraction between two arrays (i.e. matrix subtraction) to return a new array
	 * @param : Vec read-only reference other; implicit Vec parameter
	 * Returns a Vec object with same size as other and this
	 * Precondition: * this and other must be of same size, else error is thrown
	 */
	if(mySize != other.mySize)throw(invalid_argument("arrays of different sizes"));
	Vec<Item> temp(mySize);
	for(unsigned i = 0; i < mySize; i++){
		temp.setItem(i, myArray[i] - other.getItem(i));
	}
	return temp;
}

template<class Item>
void Vec<Item>::readFrom(const string& filename){
	/*
	 * Overwrites the contents of a vector using the contents of filename.txt
	 * @param read-only string reference filename, which corresponds to filename.txt in local directory
	 * Precondition: filename.txt must be properly formatted, i.e. the writeTo method format:
	 * First line contains a number indicating the length of the array
	 * Following lines contain one number to be stored in the array
	 * Precondition: number of lines after 1st line >= value of 1st line
	 * Note: completely overwrites Vec * this! Previous contents will be erased.
	 */
	delete [] myArray;
	mySize = 0;
	ifstream fin(filename.c_str());
	assert(fin.is_open());
	fin >> mySize;
	myArray = new Item[mySize];
	for(unsigned i = 0; i < mySize; i++)
	{
		fin >> myArray[i];
	}
	fin.close();
}

template<class Item>
const Item& Vec<Item>::operator[] (unsigned index) const{
	/*
	 * subscript operator used for extracting value (but not changing contents) from Vec
	 * i.e. Item other = this[index]; shortcut for Vec.getItem(index)
	 * @param unsigned index, the position in the array of the target Item
	 * @return read-only reference to Item at this.myArray[index]
	 * Precondition: the index must be less than the size of the array
	 */
	if( index >= mySize){
		throw out_of_range("Invalid subscript");
	}
	return myArray[index];
}

template<class Item>
void Vec<Item>::writeTo(string fileName) {
	/*
	 * Overwrites the contents of a file specified by filename with the contents of the Vec
	 * @param: fileName a string that is a name of a file.
	 * Precondition: fileName is a valid txt file &&
	 * 				 Vec is non default
	 * Postcondition: the file is overwritten with the contents of the Vec
	 */
	ofstream out( fileName.c_str() );
	assert(out.is_open());
	out << mySize << endl;
	for( unsigned i = 0; i < mySize; i++) {
		out << myArray[i] << endl;
	}
	out.close();
}

template<class Item>
Item& Vec<Item>::operator[] (unsigned index) {
	/*
	 * returns a reference to an item at the index, to be used for re-writing the value
	 * @param: index, an unsigned value that is a valid index value for the Vec
	 * @return: the Item at myArray[index]
	 * Precondition: index must be less than the size of the array
	 */
	if( index >= mySize){
		throw range_error("Invalid subscript");
	}
	return myArray[index];
}

template<class Item>
Vec<Item> Vec<Item>::operator+(const Vec<Item>& v2) {
	/*
	 * adds two Vecs (i.e. matrix addition)
	 * @param: v2 a Vec( and the invisible this parameter)
	 * @return: a Vec that is the two Vecs added together
	 * Precondition: Vecs must have the same size
	 */
	if(mySize == v2.mySize) {
		Vec v3(mySize);
		for( unsigned i = 0; i < mySize; i++) {
			v3.myArray[i] = myArray[i] + v2.myArray[i];
		}
		return v3;
	}
	else throw invalid_argument("Not equal sized Vecs.");
}

template<class Item>
double Vec<Item>::operator*(const Vec& v2) {
	/*
	 * multiplies two Vecs
	 * @param: v2 a Vec( and the invisible this parameter)
	 * @return: a Vec that is the two Vecs multiplied together
	 * Precondition: Vecs must have the same size
	 */
	if(mySize == v2.mySize) {
		double temp = 0;
		for( unsigned i = 0; i < mySize; i++) {
			temp = myArray[i] * v2.myArray[i] + temp;
		}
		return temp;
	}
	else throw invalid_argument("Not equal sized Vecs.");
}

template<class Item>
Vec<Item> Vec<Item>::sort(Vec<Item>& inputVec) {
	/*
	 * Recursively splits a vector into smaller pieces in order to arrange the items from least to greatest
	 * @param: inputVec - a vector that will be ordered.
	 * @return: The vector that has been sorted using the merge_sort method
	 */
	double half = 0;
	// If the size of the input vector is one, return it because it is already in order
	if (inputVec.getSize() == 1) {
		return inputVec;
	}
	// Otherwise continue the sorting
	else {
		unsigned size = inputVec.getSize();
		half = ceil((double) size /2); // Get the halfway point in the vector (If it has an even amount, it will round up)
		Vec<Item> firstHalf; // Create a temporary vector for the first half of the Vec
		Vec<Item> secondHalf; // Create a temporary vector for the second half of the Vec

		if (inputVec.getSize() % 2 == 0) {
			firstHalf.setSize(half);
			secondHalf.setSize(half);
		}
		else {
			firstHalf.setSize(half);
			secondHalf.setSize(half-1);
		}
		// First Half Assignment; The same regardless of the even or oddness of the inputVec
		for (unsigned i = 0; i < firstHalf.getSize() ; i++) {
			firstHalf[i] = inputVec[i]; // Assign the first half of the input vector to the first temporary Vec
		}
		// Second Half assignment; Contingent on whether the inputVec is even or odd
		// If it is even:
		if (inputVec.getSize() % 2 == 0) {
			for (unsigned j = firstHalf.getSize(); j < inputVec.getSize(); j++) {
				secondHalf[j-firstHalf.getSize()] = inputVec[j]; // Assign the second half of the input vector to the second temporary Vec
			}
		}
		// If it is odd:
		else {
			for (unsigned j = firstHalf.getSize(); j < inputVec.getSize(); j++) {
				secondHalf[j-firstHalf.getSize()] = inputVec[j]; // Assign the second half of the input vector to the second temporary Vec
			}
		}
		firstHalf = sort(firstHalf);
		secondHalf = sort(secondHalf);

		return merge(inputVec, firstHalf, secondHalf);
	}
}

template<class Item>
Vec<Item>& Vec<Item>::merge(Vec &input, Vec firstHalf, Vec secondHalf) {
	/*
	 * Merges two Vectors
	 * @param: vec - The vector that the two merged vectors will be written to
	 * @param: firstHalf - The first vector that will be merged
	 * @param: secondHalf - The second vector that will be merged
	 * @return: a Vec that is the two Vecs merged together
	 */
	Vec<Item> mergedVec;
	unsigned firstPos = 0, secondPos = 0, mergePos = 0; // Counter variables to iterate through the two Vecs
	mergedVec.setSize(input.getSize()); // Sets the merged vector's size to be the same as the input vector's size
	while(firstPos < firstHalf.getSize() && secondPos < secondHalf.getSize()) {  // Checks to make sure that the iterator is not passing the input Vecs' sizes
		if(firstHalf[firstPos] < secondHalf[secondPos]) { // This if and else statement checks to see which item is smaller, then appends the smaller to the result
			mergedVec.setItem(mergePos,firstHalf[firstPos]);
			firstPos++;
			mergePos++;
		}
		else { // Otherwise, append the second item because it is smaller
			mergedVec.setItem(mergePos,secondHalf[secondPos]);
			secondPos++;
			mergePos++;
		}
	}
    while(firstPos < firstHalf.getSize()) { //Puts any remaining items from the first half into the combined vector
		mergedVec.setItem(mergePos,firstHalf[firstPos]);
		firstPos++;
		mergePos++;
    }

    while(secondPos < secondHalf.getSize()) { //Puts any remaining items from the second half into the combined vector
		mergedVec.setItem(mergePos,secondHalf[secondPos]);
		secondPos++;
		mergePos++;
    }
	input = mergedVec; // Set the original vector equal to the new on and return it
	return input;
}
#endif /*PROJECT4_VEC_H_*/
