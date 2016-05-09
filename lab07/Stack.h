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
using namespace std;

typedef int Item;

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

	
protected:
	void makeCopyOf(const Stack& original);
	
private:
	unsigned myCapacity;
	unsigned myTop;
	Item*    myArray;
	friend class StackTester;
};

#endif

