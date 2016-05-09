/* Vec.cpp defines the methods for Vec, a simple vector class.
 * Student Name:
 * Date:
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */
 
#include "Vec.h"

// Default Constructor
Vec::Vec() {
	mySize = 0;
	myArray = NULL;
}

// Explicit Constructor
Vec::Vec(unsigned size) {
	mySize = size;
	Item * a = new Item[size];
	for (unsigned i = 0; i < size; i++) {
		a[i] = 0;
	}
	myArray = a;
}

// Copy Constructor
Vec::Vec(const Vec& original) {
	mySize = original.mySize;
	if (mySize > 0) {
		myArray = new Item[mySize];
		for (unsigned i = 0; i < mySize; i++) {
			myArray[i] = original.myArray[i];
		}
	};
	if (original.mySize == 0) {
		myArray = NULL;
	};
}

// Assignment Operator
Vec& Vec::operator=(const Vec& original) {
	if (mySize != original.mySize) {
		if (mySize > 0) {
			delete [] myArray;
			myArray = NULL;
		}
		if (original.mySize > 0) {
			myArray = new Item[original.mySize];
		}
		mySize = original.mySize;
	}
	for (unsigned i = 0; i < original.mySize; i++) {
		myArray[i] = original.myArray[i];
	}
	return *this;
}

// getSize()
unsigned Vec::getSize() const {
	return mySize;
}

// setItem()
void Vec::setItem(unsigned index, const Item& it) {
	if (index >= mySize) {
		throw range_error("Index out of range!");
	}
	if (index < mySize) {
		myArray[index] = it;
	}

}

// getItem()
Item Vec::getItem(unsigned index) const {
	if (index >= mySize) {
		throw range_error("Index out of range!");
	}
	if (index < mySize) {
		return myArray[index];
	}
}

// setSize()
void Vec::setSize(unsigned newSize) {
	if (newSize == 0) {
		delete [] myArray;
		myArray = NULL;
		mySize = 0;
	}
	else {
		Item * newArray = new Item[newSize];
		if (mySize < newSize) {
			for (unsigned i = 0; i < mySize; i++) {
				newArray[i] = myArray[i];
			}
			for (unsigned j = mySize; j < newSize; j++) {
				newArray[j] = 0;
			}
		}
		else if (mySize > newSize) {
			for (unsigned k = 0; k < newSize; k++) {
				newArray[k] = myArray[k];
			}
		}
		mySize = newSize;
		delete [] myArray;
		myArray = newArray;
	}
}

// Destructor
Vec::~Vec() {
	delete [] myArray;
	mySize = 0;
	myArray = NULL;
}
