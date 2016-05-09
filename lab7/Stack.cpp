/* Stack.cpp defines the dynamically allocated (array-based ) Stack operations.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 */

#include "Stack.h"

/* explicit-value constructor
 * Parameter: size, an unsigned value.
 * Precondition: size > 0.
 * Postcondition: myTop == 0 && myCapacity == size
 *              && myArray contains the address of a dynamic array of 'size' entries.
 */
Stack::Stack(unsigned size) {
   myTop = 0;
   myCapacity = size;
   myArray = new Item[size];
}

/* copy constructor
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
Stack::Stack(const Stack& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
void Stack::makeCopyOf(const Stack& original) {
	myCapacity = original.myCapacity;
	myArray = new Item[myCapacity];

	for (unsigned i = 0; i < myCapacity; i++) {
		myArray[i] = original.myArray[i];
	}
	myTop = original.myTop;
}

/* destructor
 * Postcondition: myCapacity == 0 && myTop == 0
 *             && myArray has been deallocated.
 */
Stack::~Stack() {
	delete [] myArray;
	myArray = NULL;
	myCapacity = 0;
	myTop = 0;
}

/* assignment operator
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original
 *              && I have been returned.
 */
Stack& Stack::operator=(const Stack& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

bool Stack::isEmpty() {
	if (myTop == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Stack::isFull() {
	if (myTop == myCapacity) {
		return true;
	}
	else {
		return false;
	}
}

void Stack::push(const Item& it) {
	myArray[myTop] = it;
	myTop ++;
}

Item Stack::getTop() const {
	return myArray[myTop - 1];
}

Item Stack::pop() {
	myTop--;
	return myArray[myTop];
}
