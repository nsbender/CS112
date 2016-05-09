/* BST.cpp defines binary search tree methods.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 */
 
#include "BST.h"

BST::BST() {
	myRoot = NULL;
	myNumItems = 0;
}

BST::~BST() {
	delete myRoot;
	myRoot = NULL;
	myNumItems = 0;
}

BST::Node::Node(const Item& it) {
   myItem = it;
   myLeft = NULL;
   myRight = NULL;
}

BST::Node::~Node() {
	delete myLeft;
	delete myRight;
}

bool BST::isEmpty() const {
	return myNumItems == 0;
}

void BST::insert(const Item& it) {
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

		}
	}

}

bool BST::contains(const Item& it) const {
	if (isEmpty()){
		return false;
	}
	else {
		myRoot->contains(it);
	}
}

unsigned BST::getNumItems() const {
	return myNumItems;
}

void BST::traversePreorder() {
	if ( !isEmpty() ) {
		myRoot->traversePreorder();
	}
}

void BST::traversePostorder() {
	if ( !isEmpty() ) {
		myRoot->traversePostorder();
	}
}

void BST::traverseInorder() {
	if ( !isEmpty() ) {
		myRoot->traverseInorder();
	}
}

void BST::Node::traversePreorder() {
	processItem();
	if (myLeft != NULL) {
		myLeft->traversePreorder();
	}
	if (myRight != NULL) {
		myRight->traversePreorder();
	}
}

void BST::Node::processItem() {
		cout << ' ' << myItem;
}

void BST::Node::traversePostorder() {
	if (myLeft != NULL) {
		myLeft->traversePostorder();
	}
	if (myRight != NULL) {
		myRight->traversePostorder();
	}
	processItem();
}

void BST::Node::traverseInorder() {
	if (myLeft != NULL) {
		myLeft->traverseInorder();
	}
	processItem();
	if (myRight != NULL) {
		myRight->traverseInorder();
	}
}

bool BST::Node::contains(Item it) {
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

void BST::Node::insert(Item it) {
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

