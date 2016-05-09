/* BST.h declares a "classic" binary search tree of linked nodes.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 * 
 * Class Invariant:
 *   myNumItems == 0 && myRoot == NULL ||
 *   myNumItems > 0 && 
 *     myRoot stores the address of a Node containing an item &&
 *       all items in myRoot->myLeft are less than myRoot->myItem &&
 *       all items in myRoot->myRight are greater than myRoot->myItem.
 */

#ifndef BST_H_
#define BST_H_

#include "Exception.h"
#include <iostream>
using namespace std;

typedef int Item;

template <class Item>
class BST {
public:

	BST();
	virtual ~BST();
	bool isEmpty() const;
	unsigned getNumItems() const;
	unsigned getHeight() const;
	bool contains(const Item& it) const;
	void insert(const Item& it);
	void traverseInorder();
	void traversePreorder();
	void traversePostorder();

private:
	struct Node {
	    Node(const Item& it);
            virtual ~Node();

            void traverseInorder();
            void traversePreorder();
            void traversePostorder();
            bool contains(Item it);
            void insert(Item it);
            unsigned getHeight();
            virtual void processItem();
		
            Item myItem;
            Node* myLeft;
            Node* myRight;
	};
	
	Node* myRoot;
	unsigned myNumItems;
	friend class BST_Tester;
};

template <class Item>
BST<Item>::BST() {
	myRoot = NULL;
	myNumItems = 0;
}

template <class Item>
BST<Item>::~BST() {
	delete myRoot;
	myRoot = NULL;
	myNumItems = 0;
}

template <class Item>
BST<Item>::Node::Node(const Item& it) {
   myItem = it;
   myLeft = NULL;
   myRight = NULL;
}

template <class Item>
BST<Item>::Node::~Node() {
	delete myLeft;
	delete myRight;
}

template <class Item>
bool BST<Item>::isEmpty() const {
	return myNumItems == 0;
}

template <class Item>
void BST<Item>::insert(const Item& it) {
	if (isEmpty()) {
		myRoot = new Node(it);
		myNumItems ++;
	}
	else {
		try {
			myRoot->Node::insert(it);
			myNumItems++;
		}
		catch(...) {
			throw Exception("Insert","Cannot insert this value" );
		}
	}

}

template <class Item>
bool BST<Item>::contains(const Item& it) const {
	if (isEmpty()){
		return false;
	}
	else {
		myRoot->contains(it);
	}
}

template <class Item>
unsigned BST<Item>::getNumItems() const {
	return myNumItems;
}

template <class Item>
void BST<Item>::traversePreorder() {
	if ( !isEmpty() ) {
		myRoot->traversePreorder();
	}
}

template <class Item>
void BST<Item>::traversePostorder() {
	if ( !isEmpty() ) {
		myRoot->traversePostorder();
	}
}

template <class Item>
void BST<Item>::traverseInorder() {
	if ( !isEmpty() ) {
		myRoot->traverseInorder();
	}
}

template <class Item>
void BST<Item>::Node::traversePreorder() {
	processItem();
	if (myLeft != NULL) {
		myLeft->traversePreorder();
	}
	if (myRight != NULL) {
		myRight->traversePreorder();
	}
}

template <class Item>
void BST<Item>::Node::processItem() {
		cout << ' ' << myItem;
}

template <class Item>
void BST<Item>::Node::traversePostorder() {
	if (myLeft != NULL) {
		myLeft->traversePostorder();
	}
	if (myRight != NULL) {
		myRight->traversePostorder();
	}
	processItem();
}

template <class Item>
void BST<Item>::Node::traverseInorder() {
	if (myLeft != NULL) {
		myLeft->traverseInorder();
	}
	processItem();
	if (myRight != NULL) {
		myRight->traverseInorder();
	}
}

template <class Item>
bool BST<Item>::Node::contains(Item it) {
	if (it < myItem) {
		if (myLeft == NULL) {
			return false;
		}
		else {
			myLeft->contains(it);
		}
	}
	else if (it > myItem) {
		if (myRight == NULL) {
			return false;
		}
		else {
			myRight->contains(it);
		}
	}
	else if (it == myItem) {
		return true;
	}
}

template <class Item>
void BST<Item>::Node::insert(Item it) {
	if (it < myItem) {
		if (myLeft == NULL)
			myLeft = new Node(it);
		else {
			myLeft->insert(it);
		}
	}
	else if (it > myItem) {
		if (myRight == NULL) {
			myRight = new Node(it);
		}
		else {
			myRight->insert(it);
		}
	}
	else if (it == myItem) {
		throw(Exception("In Node::insert()","This item already exists in the BST"));
	}
}

template <class Item>
unsigned BST<Item>::getHeight() const {
	if ( isEmpty () == true ) {
		return 0;
	}
	else {
		return myRoot->getHeight();
	}
}

template <class Item>
unsigned BST<Item>::Node::getHeight() {
	int leftHeight, rightHeight;
	// Recursively Calls getHeight if a left or right isnt NULL, otherwise adds 0 since there is no height
	if ( myLeft != NULL ) {
		leftHeight = myLeft->getHeight();
	}
	else {
		leftHeight = 0;
	}
	if ( myRight != NULL ) {
		rightHeight = myRight->getHeight();
	}
	else {
		rightHeight = 0;
	}
	// Increments the size of each half and adds one extra level to the counter if one side is bigger.
	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}
}

#endif /*BST_H_*/

