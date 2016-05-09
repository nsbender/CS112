/*
 * List.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: nsb2
 */

#include "List.h"

List::List() {
	mySize = 0;
	myFirst = NULL;
	myLast = NULL;
}

List::Node::Node() {
	myItem = 0;
	myNext = NULL;
}

List::Node::Node(int item, Node * ptr) {
	myItem = item;
	myNext = ptr;
}

unsigned List::getSize() const {
	return mySize;
}

Item List::getFirst() const {
	if ( (mySize > 0) && (myFirst != NULL) ) {
		return myFirst->myItem;
	}
	else {
		throw underflow_error("NO LIST FOUND!");
	}
}

Item List::getLast() const {
	if ( (mySize > 0) && (myLast != NULL) ) {
		return myLast->myItem;
	}
	else {
		throw underflow_error("NO LIST FOUND!");
	}
}

void List::append(const Item& it) {
	Node * nodePtr = new Node(it, NULL);
	if (mySize == 0) {
		myFirst = nodePtr;
	}
	else {
		myLast->myNext = nodePtr;
	}
	myLast = nodePtr;
	mySize ++;
}

List::~List() {
	Node* first = myFirst;     // initialize both to point at the first node
	Node* next = first;
	while (first != NULL) {    // while there are nodes to be processed:
		next = first->myNext;   //   save the address of the next node
		first->myItem = 0;      //   clear myItem in first node (optional)
		first->myNext = NULL;   //   clear myNext in first node (optional)
		delete first;           //   delete the first node
		first = next;           //   make first point to the next node
	}
	myFirst = myLast = NULL;
	mySize = 0;
}

List::List(const List& original) {
	myFirst = myLast = NULL;          //  set pointers
	mySize = 0;                       //   and size to 'empty' values
	if (original.getSize() > 0) {     //  if there are nodes to copy:
		Node* oPtr = original.myFirst; //  start at the first node
		while (oPtr != NULL) {         //  while there are more nodes:
			append(oPtr->myItem);       //   append the item in that node
			oPtr = oPtr->myNext;        //   advance to next node
		}
	}
}

List& List::operator=(const List& original) {
	if (myFirst != original.myFirst) {
		this->~List();
		myFirst = myLast = NULL;
		mySize = 0;
		if (original.getSize() > 0) {     //  if there are nodes to copy:
			Node* nPtr = original.myFirst; //  start at the first node
			while (nPtr != NULL) {         //  while there are more nodes:
				append(nPtr->myItem);       //   append the item in that node
				nPtr = nPtr->myNext;        //   advance to next node
			}
		}
	}
	return * this;
}
