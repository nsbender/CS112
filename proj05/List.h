/*
 * List.h
 *
 *  Created on: Mar 10, 2015
 *      Author: Mitch
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>
using namespace std;


template <class Item>
class List {
public:
	List();
	virtual ~List();
	List(const List<Item>& original);
	void append(Item it);
	unsigned getSize() const;
	List<Item>& operator=(const List<Item>& original);
	Item getFirst() const;
	Item getLast() const;
	bool operator==(const List<Item>& original) const;
	bool operator!=(const List<Item>& original) const;
	void readFrom(istream& in);
	void writeTo(ostream& out);
	void readFrom(string filename);
	void writeTo(string filename);
	void prepend(Item it);
	int getIndexOf(Item it);
	void insert(Item it, unsigned index);
	int remove(unsigned idx);


private:
	unsigned mySize;
	struct Node {
		Node();
		Node(Item data, Node * next);
		virtual ~Node();
		Item myItem;
		Node * myNext;
	};
	Node * myFirst;
	Node * myLast;
	friend class ListTester;
};

template <class Item>
List<Item>::List() {
	myFirst = NULL;
	myLast = NULL;
	mySize = 0;
}

template <class Item>
List<Item>::Node::Node() {
	myItem = 0;
	myNext = NULL;
}

template <class Item>
List<Item>::Node::Node(Item data, Node * next) {
	myItem = data;
	myNext = next;
}

template <class Item>
List<Item>::List(const List<Item>& original) {
	myFirst = myLast = NULL;
	mySize = 0;
	if (original.getSize() > 0) {
		Node * n = original.myFirst;
		while (n != NULL) {
			append(n->myItem);
			n = n->myNext;
		}
	}
}

template <class Item>
List<Item>::~List() {
	delete myFirst;
	myFirst = myLast = NULL;
	mySize = 0;
}

template <class Item>
List<Item>::Node::~Node() {
	delete myNext;
	myNext = NULL;
	myItem = 0;
}

template <class Item>
void List<Item>::append(Item it) {
	if (mySize == 0) {
		Node * n = new Node(it, NULL);
		myFirst = n;
		myLast = n;
		mySize++;
	}
	else {
		//size is greater than 0
		Node * n = new Node(it, NULL);
		myLast->myNext = n;
		myLast = n;
		mySize++;
	}
}

template <class Item>
List<Item>& List<Item>::operator=(const List<Item>& original) {
	if (this != &original) {
		this->~List();
		if (original.getSize() > 0) {
			Node * n = original.myFirst;
			while (n != NULL) {
				append(n->myItem);
				n = n->myNext;
			}
		}
	}
	return *this;
}

template <class Item>
unsigned List<Item>::getSize() const{
	return mySize;
}

template <class Item>
Item List<Item>::getFirst() const{
	if ((myFirst != NULL) && (mySize > 0)) {
		return myFirst->myItem;
	}
	else {
		throw underflow_error("Not allowed.");
	}

}

template <class Item>
Item List<Item>::getLast() const{
	if (mySize > 0) {
		return myLast->myItem;
	}
	else {
		throw underflow_error("Not allowed.");
	}
}

template <class Item>
bool List<Item>::operator==(const List<Item>& original) const {
	/* Written by: Mitch Stark
	 * Purpose: test equality of two lists
	 * return: boolean value of the equality of the lists
	 */
	if (mySize == original.getSize()) {
		Node * ptr = myFirst;
		Node * optr = original.myFirst;
		for (unsigned i = 0; i < mySize; i++) {
			if (ptr->myItem != optr->myItem) {
				return false;
			}
			ptr = ptr->myNext;
			optr = optr->myNext;
		}
		return true;
	}
	return false;
}

template <class Item>
bool List<Item>::operator!=(const List<Item>& original) const {
	/* Written by: Nate Bender
	 * Purpose: test for inequality between two lists
	 * return: boolean value of the inequality of the lists
	 */
	if (mySize == original.getSize()) {
		Node * ptr = myFirst;
		Node * optr = original.myFirst;
		for (unsigned i = 0; i < mySize; i++) {
			if (ptr->myItem != optr->myItem) {
				return true;
			}
			ptr = ptr->myNext;
			optr = optr->myNext;
		}
		return false;
	}
	else {
		return true;
	}
}

template <class Item>
void List<Item>::readFrom(istream& in){
	/*
	 * Written by: Mitch Stark
	 * Purpose: read a list in from a stream
	 * return: nothing
	 */
	unsigned size;
	Item val;
	while (!in.eof()) {
		in >> val;
		append(val);
	}
}

template <class Item>
void List<Item>::writeTo(ostream& out){
	/*
	 * Written by: Nate Bender
	 * Purpose: write a list to a stream
	 * return: nothing
	 */
	Node * ptr = myFirst;
	out << ptr -> myItem;
	ptr = ptr -> myNext;
	for (unsigned i = 1; i < mySize; i++) {
		out << "\n";
		out << ptr -> myItem;
		ptr = ptr -> myNext;
	}
}

template <class Item>
void List<Item>::readFrom(string filename) {
	/*
	 * Written by: Nate Bender
	 * Purpose: write a list to a file
	 * return: nothing
	 */
	Item line;
	ifstream fin(filename.c_str());
	assert(fin.is_open());
	if (myFirst != NULL) {
		this -> ~List();
	}
	mySize = 0;
	while (!fin.eof()) {
		fin >> line;
		this -> append(line);
	}
	fin.close();
}

template <class Item>
void List<Item>::writeTo(string filename) {
	/*
	 * Written by: Mitch Stark
	 * Purpose: write a list to a file
	 * return: nothing
	 */
	ofstream fout(filename.c_str());
	assert(fout.is_open());
	Node * ptr = myFirst;
	for (unsigned i = 0; i < mySize; i++) {
		fout << ptr->myItem << '\n';
		ptr = ptr->myNext;
	}
}

template <class Item>
void List<Item>::prepend(Item it) {
	/*
	 * Written by: Mitch Stark
	 * Purpose: add an item to the beginning of a list
	 * return: nothing
	 */
	if (mySize > 0) {
		Node * n = new Node(it, myFirst);
		myFirst = n;
		mySize++;
	}
	else {
		append(it);
	}
}

template <class Item>
int List<Item>::getIndexOf(Item it) {
	/*
	 * Written by: Nate Bender
	 * purpose: search for an item and return its location if found
	 */
	Node * ptr = myFirst;
	for (unsigned i = 0; i < mySize; i++) {
		if (ptr -> myItem == it) {
			return i;
		}
		ptr = ptr->myNext;
	}
	return -1;
}

template <class Item>
void List<Item>::insert(Item it, unsigned index) {
	/*
	 * Written by: Mitch Stark
	 * purpose: add in an item to a list at a given spot
	 */
	if ((index > (mySize + 1)) || (index < 0)){
		throw range_error("Invalid range");
	}

	if (index == 0) {
		prepend(it);
	}
	else if (index == (mySize + 1)) {
		append(it);
	}
	else {
		Node * ptr = myFirst;
		for (unsigned i = 0; i < index; i++) {
			ptr = ptr->myNext;
		}
		Node * n = new Node(it, NULL);
		n->myNext = ptr->myNext;
		ptr->myNext = n;
	}

}

template <class Item>
int List<Item>::remove(unsigned idx) {
	/*
	 * Written by: Nate Bender
	 * purpose: removes the node at the specified index
	 */
	Node * ptr = myFirst;
	Node * ptr2 = myFirst;
	Node * ptr3 = myFirst;
	for (unsigned i = 0; i < idx; i++) {
		ptr = ptr->myNext;
	}
	for (unsigned j = 0; j < idx+1; j++) {
		ptr2 = ptr2->myNext;
	}
	for (unsigned k = 0; k < idx-1; k++) {
		ptr3 = ptr3->myNext;
	}

	Item value = ptr -> myItem;
	ptr = myFirst;
	for (unsigned i = 0 ; i < mySize -1 ; i++) {
		ptr = ptr -> myNext;
	}
	myLast -> myItem = ptr -> myItem;
	ptr3 -> myNext = ptr2;
	mySize--;
	return value;
}


#endif /* LIST_H_ */
