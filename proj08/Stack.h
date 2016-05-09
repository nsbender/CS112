/* Stack.h provides a (dynamic-array-based) Stack class.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 * 
 * Invariant: myTop == 0 && isEmpty() && !isFull()
 *         || myTop == myCapacity && !isEmpty() && isFull()
 *         || myTop > 0 && myTop < myCapacity && !isEmpty() && !isFull().
 * Notes: 
 * 1. Member myTop always contains the index of the next empty space in myArray
 *        (the index of the array element into which the next pushed item will be placed).
 * 2. Sending push() to a full Stack throws the exception Stack::Overflow.
 * 3. Sending pop() or getTop() to an empty Stack throws the exception Stack::Underflow.
 */

#ifndef STACK_H_
#define STACK_H_

//#include "StackException.h"
#include <string>
#include <iostream>
#include "StackException.h"
#include <cctype>
#include <fstream>
using namespace std;

template<class Item>

class Stack {
public:
	Stack(unsigned size);
	Stack(const Stack& original);
	~Stack();
	Stack& operator=(const Stack& original);
	bool isEmpty();
	bool isFull();
	void push(const Item& it);
	Item getTop() const;
	Item pop();
	unsigned getSize() const {return myTop;};
	unsigned getCapacity () const {return myCapacity;};
	void setCapacity(unsigned cap);
	void decode(ifstream fin);
	
protected:
	void makeCopyOf(const Stack& original);
	
private:
	unsigned myCapacity;
	unsigned myTop;
	Item*    myArray;
	friend class StackTester;
};

/* explicit-value constructor
 * Parameter: size, an unsigned value.
 * Precondition: size > 0.
 * Postcondition: myTop == 0 && myCapacity == size
 *              && myArray contains the address of a dynamic array of 'size' entries.
 */
template<class Item>
Stack<Item>::Stack(unsigned size) {
	if (size > 0) {
		myTop = 0;
		myCapacity = size;
		myArray = new Item[size];
	}
	else {
		throw StackException("Stack(size)","size must be positive!");
	}
}

/* copy constructor
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template<class Item>
Stack<Item>::Stack(const Stack& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template<class Item>
void Stack<Item>::makeCopyOf(const Stack& original) {
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
template<class Item>
Stack<Item>::~Stack() {
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
template<class Item>
Stack<Item>& Stack<Item>::operator=(const Stack& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

template<class Item>
bool Stack<Item>::isEmpty() {
	if (myTop == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<class Item>
bool Stack<Item>::isFull() {
	if (myTop == myCapacity) {
		return true;
	}
	else {
		return false;
	}
}

template<class Item>
void Stack<Item>::push(const Item& it) {
	if (isFull() == false) {
		myArray[myTop] = it;
		myTop ++;
	}
	else {
		throw StackException("push()", "stack is full!");
	}
}

template<class Item>
Item Stack<Item>::getTop() const {
	if (myTop > 0) {
		return myArray[myTop - 1];
	}
	else {
		throw StackException("getTop()", "stack is empty!");
	}
}

template<class Item>
Item Stack<Item>::pop() {
	if (myTop > 0) {
		myTop--;
		return myArray[myTop];
	}
	else {
		throw StackException("pop()", "stack is empty!");
	}
}

template<class Item>
void Stack<Item>::setCapacity(unsigned cap) {
	Item * newArray;
	newArray = new Item[cap];
	if (myCapacity < cap) {
		for (unsigned i = 0 ; i < myCapacity ; i++) {
			newArray[i] = myArray[i];
		}
		for (unsigned j = myCapacity ; j < cap ; j++) {
			newArray[j] = 0;
		}
	}
	else {
		for (unsigned i = 0 ; i < cap ; i++) {
			newArray[i] = myArray[i];
		}
		if (myTop > cap) {
			myTop = cap;
		}
	}
	delete [] myArray;
	myArray = newArray;
	myCapacity = cap;
}

#endif

