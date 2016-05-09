/* testSetCapacity() for an array-based Queue class.
 * Author: Dan Brown, for CS 112 at Calvin College.
 * Date: May, 2008.
 */

#include "ArrayQueueTester.h"

void ArrayQueueTester::testSetCapacity(){
	
	cout << "Testing setCapacity()..." << flush;

	//Test changing capacity on an empty queue
	ArrayQueue<int> q1(1);
	assert( q1.getCapacity() == 1 );
	assert( q1.getSize() == 0 );
	assert( q1.isEmpty() );
	assert( !q1.isFull() );

	//increase the capacity
	q1.setCapacity(10);
	assert( q1.getCapacity() == 10 );
	assert( q1.getSize() == 0 );
	assert( q1.isEmpty() );
	assert( !q1.isFull() );
	cout << " 1a" << flush;

	//decrease the capacity
	q1.setCapacity(5);
	assert( q1.getCapacity() == 5 );
	assert( q1.getSize() == 0 );
	assert( q1.isEmpty() );
	assert( !q1.isFull() );
	cout << " 1b" << flush;

	//try setting the capacity to zero
	try{
		q1.setCapacity(0);
		cerr << "setCapacity(0) worked!" << endl;
		exit(1);
	} catch ( QueueException e ) {
		//check to make sure nothing was changed
		assert( q1.getCapacity() == 5 );
		assert( q1.getSize() == 0 );
		assert( q1.isEmpty() );
		assert( !q1.isFull() );
		cout << " 1c" << flush;

	}

	//Test changing capacity on a queue with items that
	//start at the beginning of the array
	ArrayQueue<int> q2(5);
	for (int i = 0; i < 5; i++){
		q2.append(i+1);
	}
	assert( q2.getCapacity() == 5 );
	assert( q2.getSize() == 5 );
	assert( !q2.isEmpty() );
	assert( q2.isFull() );
	assert( q2.getFirst() == 1 );
	assert( q2.getLast() == 5 );

	//increase the capacity
	q2.setCapacity(10);
	assert( q2.getCapacity() == 10 );
	assert( q2.getSize() == 5 );
	assert( !q2.isEmpty() );
	assert( !q2.isFull() );
	assert( q2.getFirst() == 1 );
	assert( q2.getLast() == 5 );
	cout << " 2a" << flush;

	//check to make sure appending still works
	q2.append(6);
	assert( q2.getLast() == 6 );
	q2.append(7);
	q2.append(8);
	q2.append(9);
	q2.append(10);
	assert( q2.getCapacity() == 10 );
	assert( q2.getSize() == 10 );
	assert( !q2.isEmpty() );
	assert( q2.isFull() );
	assert( q2.getFirst() == 1 );
	assert( q2.getLast() == 10 );
	cout << " 2b" << flush;

	//check to make sure that removing still works
	assert( q2.remove() == 1 );
	assert( q2.remove() == 2 );
	assert( q2.remove() == 3 );
	assert( q2.remove() == 4 );
	assert( q2.remove() == 5 );
	assert( q2.remove() == 6 );
	assert( q2.remove() == 7 );
	assert( q2.remove() == 8 );
	assert( q2.remove() == 9 );
	assert( q2.remove() == 10 );
	assert( q2.getCapacity() == 10 );
	assert( q2.getSize() == 0 );
	assert( q2.isEmpty() );
	assert( !q2.isFull() );
	cout << " 2c" << flush;

	//set up a clean queue before continuing...
	ArrayQueue<int> q3(20);
	for (int i = 0; i < 5; i++){
		q3.append(i+1);
	}
	assert( q3.getCapacity() == 20 );
	assert( q3.getSize() == 5 );
	assert( !q3.isEmpty() );
	assert( !q3.isFull() );
	assert( q3.getFirst() == 1 );
	assert( q3.getLast() == 5 );

	//decrease the capacity
	q3.setCapacity(10);
	assert( q3.getCapacity() == 10 );
	assert( q3.getSize() == 5 );
	assert( !q3.isEmpty() );
	assert( !q3.isFull() );
	assert( q3.getFirst() == 1 );
	assert( q3.getLast() == 5 );
	cout << " 2d" << flush;
	
	//check to make sure appending still works
	q3.append(6);
	assert( q3.getLast() == 6 );
	q3.append(7);
	q3.append(8);
	q3.append(9);
	q3.append(10);
	assert( q3.getCapacity() == 10 );
	assert( q3.getSize() == 10 );
	assert( !q3.isEmpty() );
	assert( q3.isFull() );
	assert( q3.getFirst() == 1 );
	assert( q3.getLast() == 10 );
	cout << " 2e" << flush;

	//check to make sure that removing still works
	assert( q3.remove() == 1 );
	assert( q3.remove() == 2 );
	assert( q3.remove() == 3 );
	assert( q3.remove() == 4 );
	assert( q3.remove() == 5 );
	assert( q3.remove() == 6 );
	assert( q3.remove() == 7 );
	assert( q3.remove() == 8 );
	assert( q3.remove() == 9 );
	assert( q3.remove() == 10 );
	assert( q3.getCapacity() == 10 );
	assert( q3.getSize() == 0 );
	assert( q3.isEmpty() );
	assert( !q3.isFull() );
	cout << " 2f" << flush;

	//test setCapacity() on a queue that has items starting
	//in the middle of the array, not wrapping around
	ArrayQueue<int> q4(5);
	for (int i = 0; i < 5; i++){
		q4.append(i+1);
	}
	q4.remove();
	q4.remove();
	assert( q4.getCapacity() == 5 );
	assert( q4.getSize() == 3 );
	assert( !q4.isEmpty() );
	assert( !q4.isFull() );
	assert( q4.getFirst() == 3 );
	assert( q4.getLast() == 5 );

	//increase the capacity
	q4.setCapacity(10);
	assert( q4.getCapacity() == 10 );
	assert( q4.getSize() == 3 );
	assert( !q4.isEmpty() );
	assert( !q4.isFull() );
	assert( q4.getFirst() == 3 );
	assert( q4.getLast() == 5 );
	cout << " 3a" << flush;

	//check to make sure appending still works
	q4.append(6);
	q4.append(7);
	q4.append(8);
	q4.append(9);
	q4.append(10);
	q4.append(11);
	q4.append(12);
	assert( q4.getCapacity() == 10 );
	assert( q4.getSize() == 10 );
	assert( !q4.isEmpty() );
	assert( q4.isFull() );
	assert( q4.getFirst() == 3 );
	assert( q4.getLast() == 12 );
	cout << " 3b" << flush;

	//check to make sure removing still works
	assert( q4.remove() == 3 );
	assert( q4.remove() == 4 );
	assert( q4.remove() == 5 );
	assert( q4.remove() == 6 );
	assert( q4.remove() == 7 );
	assert( q4.remove() == 8 );
	assert( q4.remove() == 9 );
	assert( q4.remove() == 10 );
	assert( q4.remove() == 11 );
	assert( q4.remove() == 12 );
	assert( q4.getCapacity() == 10 );
	assert( q4.getSize() == 0 );
	assert( q4.isEmpty() );
	assert( !q4.isFull() );
	cout << " 3c" << flush;

	//create a clean queue before continuing...
	ArrayQueue<int> q5(10);
	for (int i = 0; i < 10; i++){
		q5.append(i+1);
	}
	for (int i = 0; i < 7; i++){
		q5.remove();
	}
	assert( q5.getCapacity() == 10 );
	assert( q5.getSize() == 3 );
	assert( !q5.isEmpty() );
	assert( !q5.isFull() );
	assert( q5.getFirst() == 8 );
	assert( q5.getLast() == 10 );

	//reduce the capacity
	q5.setCapacity(5);
	assert( q5.getCapacity() == 5 );
	assert( q5.getSize() == 3 );
	assert( !q5.isEmpty() );
	assert( !q5.isFull() );
	assert( q5.getFirst() == 8 );
	assert( q5.getLast() == 10 );
	cout << " 3d" << flush;

	//check to make sure appending still works
	q5.append(11);
	q5.append(12);
	assert( q5.getCapacity() == 5 );
	assert( q5.getSize() == 5 );
	assert( !q5.isEmpty() );
	assert( q5.isFull() );
	assert( q5.getFirst() == 8 );
	assert( q5.getLast() == 12 );
	cout << " 3e" << flush;

	//check to make sure removing still works
	assert( q5.remove() == 8 );
	assert( q5.remove() == 9 );
	assert( q5.remove() == 10 );
	assert( q5.remove() == 11 );
	assert( q5.remove() == 12 );
	assert( q5.getCapacity() == 5 );
	assert( q5.getSize() == 0 );
	assert( q5.isEmpty() );
	assert( !q5.isFull() );
	cout << " 3f" << flush;

	//test setCapacity() on a queue with values that
	//wrap around the array
	ArrayQueue<int> q6(5);
	for (int i = 0; i < 5; i++){
		q6.append(i+1);
	}
	q6.remove();
	q6.remove();
	q6.remove();
	q6.append(6);
	q6.append(7);
	assert( q6.getCapacity() == 5 );
	assert( q6.getSize() == 4 );
	assert( !q6.isEmpty() );
	assert( !q6.isFull() );
	assert( q6.getFirst() == 4 );
	assert( q6.getLast() == 7 );

	//increase the capacity
	q6.setCapacity(10);
	assert( q6.getCapacity() == 10 );
	assert( q6.getSize() == 4 );
	assert( !q6.isEmpty() );
	assert( !q6.isFull() );
	assert( q6.getFirst() == 4 );
	assert( q6.getLast() == 7 );
	cout << " 4a" << flush;

	//check to make sure appending still works
	q6.append(8);
	q6.append(9);
	q6.append(10);
	q6.append(11);
	q6.append(12);
	q6.append(13);
	assert( q6.getCapacity() == 10 );
	assert( q6.getSize() == 10 );
	assert( !q6.isEmpty() );
	assert( q6.isFull() );
	assert( q6.getFirst() == 4 );
	assert( q6.getLast() == 13 );
	cout << " 4b" << flush;

	//check to make sure removing still works
	assert( q6.remove() == 4 );
	assert( q6.remove() == 5 );
	assert( q6.remove() == 6 );
	assert( q6.remove() == 7 );
	assert( q6.remove() == 8 );
	assert( q6.remove() == 9 );
	assert( q6.remove() == 10 );
	assert( q6.remove() == 11 );
	assert( q6.remove() == 12 );
	assert( q6.remove() == 13 );
	assert( q6.getCapacity() == 10 );
	assert( q6.getSize() == 0 );
	assert( q6.isEmpty() );
	assert( !q6.isFull() );
	cout << " 4c" << flush;

	//set up a clean queue before continuing...
	ArrayQueue<int> q7(10);
	for(int i = 0; i < 10; i++){
		q7.append(i+1);
	}
	for(int i = 0; i < 8; i++){
		q7.remove();
	}
	q7.append(11);
	q7.append(12);
	assert( q7.getCapacity() == 10 );
	assert( q7.getSize() == 4 );
	assert( !q7.isEmpty() );
	assert( !q7.isFull() );
	assert( q7.getFirst() == 9 );
	assert( q7.getLast() == 12 );

	//reduce the capacity
	q7.setCapacity(6);
	assert( q7.getCapacity() == 6 );
	assert( q7.getSize() == 4 );
	assert( !q7.isEmpty() );
	assert( !q7.isFull() );
	assert( q7.getFirst() == 9 );
	assert( q7.getLast() == 12 );
	cout << " 4d" << flush;

	//check to make sure appending still works
	q7.append(13);
	q7.append(14);
	assert( q7.getCapacity() == 6 );
	assert( q7.getSize() == 6 );
	assert( !q7.isEmpty() );
	assert( q7.isFull() );
	assert( q7.getFirst() == 9 );
	assert( q7.getLast() == 14 );
	cout << " 4e" << flush;

	//check to make sure removing still works
	assert( q7.remove() == 9 );
	assert( q7.remove() == 10 );
	assert( q7.remove() == 11 );
	assert( q7.remove() == 12 );
	assert( q7.remove() == 13 );
	assert( q7.remove() == 14 );
	assert( q7.getCapacity() == 6 );
	assert( q7.getSize() == 0 );
	assert( q7.isEmpty() );
	assert( !q7.isFull() );
	cout << " 4f" << flush;

	//try reducing capacity to less than the current size
	ArrayQueue<int> q8(10);
	for( int i = 0; i < 8; i++){
		q8.append(i+1);
	}
	assert( q8.getCapacity() == 10 );
	assert( q8.getSize() == 8 );
	assert( !q8.isEmpty() );
	assert( !q8.isFull() );
	assert( q8.getFirst() == 1 );
	assert( q8.getLast() == 8 );
	
	try{
		q8.setCapacity(5);
		cerr << "setCapacity worked with new capacity < size" << endl;
		exit(1);
	} catch (QueueException e) {
		//check to make sure nothing changed
		assert( q8.getCapacity() == 10 );
		assert( q8.getSize() == 8 );
		assert( !q8.isEmpty() );
		assert( !q8.isFull() );
		assert( q8.getFirst() == 1 );
		assert( q8.getLast() == 8 );
		assert( q8.remove() == 1 );
		assert( q8.remove() == 2 );
		assert( q8.remove() == 3 );
		assert( q8.remove() == 4 );
		assert( q8.remove() == 5 );
		assert( q8.remove() == 6 );
		assert( q8.remove() == 7 );
		assert( q8.remove() == 8 );
		cout << " 5" << flush;
	}

	// copy a full queue, where myFirst && myLast are not zero,
	// so newer items precede older items in the queue
	// (thanks to Christpher Hesters).
	ArrayQueue<int> q9(3);
	q9.append(11);
	q9.append(12);
	q9.append(13);
	assert(q9.remove() == 11);
	q9.append(14);
	assert(q9.remove() == 12);
	q9.append(15);
	q9.setCapacity(4);
	assert(q9.getCapacity() == 4);
	assert(q9.getFirst() == 13);
	assert(q9.getLast() == 15);
	assert(q9.remove() == 13);
	assert(q9.getFirst() == 14);
	assert(q9.getLast() == 15);
	assert(q9.remove() == 14);
	assert(q9.getFirst() == 15);
	assert(q9.getLast() == 15);
	assert(q9.remove() == 15);
	cout << " 6" << flush;

	cout << " Passed!" << endl;

}	
