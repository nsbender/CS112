/* ArrayQueue.h declares a Queue class using a dynamic array.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name: Nate Bender
 * Date: 4/17/15
 * 
 * Class Invariant: 
 *    mySize == 0 ||
 *    mySize > 0 && myArray[myFirst] == getFirst()
 *               && myArray[myLast-1] == getLast().
 * 
 *  (When I am not empty:
 *     myFirst is the index of my oldest value;
 *     myLast is the index of the spot where the next
 *       item to be appended will be placed.)      
 */

#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include "QueueException.h"
#include <cstring>      // memcpy()

typedef double Item;

template <class Item>
class ArrayQueue {
public:

	ArrayQueue(unsigned capacity);
	ArrayQueue(const ArrayQueue<Item>& original);
	virtual ~ArrayQueue();
	ArrayQueue<Item>& operator=(const ArrayQueue<Item>& original);
	unsigned getSize() const;
	unsigned getCapacity() const;
	void setCapacity(unsigned capacity);
	bool isEmpty() const;
	bool isFull() const;
	void append(const Item& it);
	Item getFirst() const;
	Item getLast() const;
	Item remove();

protected:
	virtual void makeCopyOf(const ArrayQueue<Item>& original);
private:
	unsigned mySize;       // number of items I contain
	unsigned myCapacity;   // how many items I can store
	unsigned myFirst;      // index of oldest item (if any)
	unsigned myLast;       // index of next available spot for append (if any)
	Item*    myArray;      // dynamic array of items

	friend class ArrayQueueTester;
};

template <class Item>
ArrayQueue<Item>::ArrayQueue(unsigned capacity) {
	if (capacity > 0) {
		myCapacity = capacity;
		mySize = 0;
		myFirst = myLast = 0;
		myArray = new Item[capacity];
	}
	else {
		throw(QueueException("In ArrayQueue Constructor", "Queue of negative Size!" ));
	}
}

template <class Item>
ArrayQueue<Item>::ArrayQueue(const ArrayQueue<Item>& original) {
	makeCopyOf(original);
}

template <class Item>
void ArrayQueue<Item>::makeCopyOf(const ArrayQueue<Item>& original) {
	mySize = original.mySize;
	myCapacity = original.myCapacity;
	myFirst = original.myFirst;
	myLast = original.myLast;
	myArray = new Item[myCapacity];
	memcpy(myArray, original.myArray, myCapacity*sizeof(Item) );
}

template <class Item>
ArrayQueue<Item>::~ArrayQueue() {
	delete [] myArray;
	myArray = NULL;
	mySize = myFirst = myLast = 0;
}

template <class Item>
ArrayQueue<Item>& ArrayQueue<Item>::operator=(const ArrayQueue<Item>& aQueue) {
	if (this != &aQueue) {
		delete [] myArray;
		makeCopyOf(aQueue);
	}
	return *this;
}

template <class Item>
bool ArrayQueue<Item>::isEmpty() const {
	return mySize == 0;
}

template <class Item>
bool ArrayQueue<Item>::isFull() const {
	return getSize() == myCapacity;
}

template <class Item>
unsigned ArrayQueue<Item>::getCapacity() const {
	return myCapacity;
}

template <class Item>
void ArrayQueue<Item>::setCapacity(unsigned capacity) {
	if (capacity > 0) {
		if ( capacity >= getSize()) {
			Item * newArray= new Item[capacity];
			unsigned size = mySize;
			for (unsigned i = 0 ; i < size ; i++) {
				newArray[i] = remove();
			}
			delete [] myArray;
			myArray = newArray;
			myFirst = 0;
			myLast = size;
			mySize = size;
			myCapacity = capacity;
		}
		else {
			throw QueueException("Exception in setCapacity","Cannot resize a queue to be smaller than the original!");
		}
	}
	else {
		throw QueueException("Exception in setCapacity","Cannot resize a queue to capacity 0!");
	}
}

template <class Item>
unsigned ArrayQueue<Item>::getSize() const {
	return mySize;
}

template <class Item>
Item ArrayQueue<Item>::getFirst() const {
	if (! isEmpty())
	{
		return myArray[myFirst];
	}
	else {
		throw EmptyQueueException("Cannot get first element from an empty queue");
	}
}

template <class Item>
Item ArrayQueue<Item>::getLast() const {
	if (! isEmpty())
	{
		return myArray[(myLast-1+myCapacity) % myCapacity];
	}
	else {
		throw EmptyQueueException("Cannot get last element from an empty queue");
	}
}

template <class Item>
void ArrayQueue<Item>::append(const Item& it) {
	if (isFull()) {
		throw FullQueueException("Cannot Append to a full Queue");
	}
	else {
		myArray[myLast] = it;
		myLast = (myLast % myCapacity) + 1;
		mySize ++;
	}
}

template <class Item>
Item ArrayQueue<Item>::remove() {
	if (isEmpty()) {
		throw EmptyQueueException("Cannot remove from an empty queue");
	}
	else {
		Item result = myArray[myFirst];
		myFirst = (myFirst % myCapacity) + 1;
		mySize--;
		return result;
	}
}

#endif /*ARRAY_QUEUE_H_*/
