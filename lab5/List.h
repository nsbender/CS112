/*
 * List.h
 *
 *  Created on: Mar 10, 2015
 *      Author: nsb2
 */

#ifndef LIST_H_
#define LIST_H_

#include <cstdlib>
#include <stdexcept>
using namespace std;

typedef double Item;

class List {

public:
	List();
	Item getFirst() const;
	Item getLast() const;
	unsigned getSize() const;
	void append(const Item& it);
	~List();
	List(const List& original);
	List& operator=(const List& original);

private:
	struct Node {
		Node();
		Node(int item, Node * ptr);
		Item myItem;
		Node * myNext;
	};
	unsigned mySize;
	Node * myFirst;
	Node * myLast;

	friend class ListTester;
};



#endif /* LIST_H_ */
