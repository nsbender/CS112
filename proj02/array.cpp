/* array.cpp defines "C style" array operations
 * Student: Nate Bender
 * Date: 2/23/15
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */
 
#include "array.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void initialize(double *a, int size) {
	int val = 0;
	for (int i = 0; i < size; i++) {
		val = i+1;
		a[i] = val;
	}
}
 
void print(double *a, int size) {
	for (int i = 0; i < size; i++) {
		cout << *a << '\t';
		a++;
	}
}		

/* average() returns the average value of all objects in the array.
 *
 * @param: double *a, an array full of doubles, int size, the size of the array
 * @return: the value of all of the objects in the array averaged
 */
double average(double *a, int size) {
	double sumValue = 0;
	double averageValue = 0;
	for (int i = 0; i < size; i++) {
		sumValue += a[i];
	}
	averageValue = sumValue / size;
	return averageValue;
}

/* sum() returns the sum value of all objects in the array.
 *
 * @param: double *a, an array full of doubles, int size, the size of the array
 * @return: the value of all of the objects in the array added
 */
double sum(double *a, int size)
{
	double sumValue = 0;
	for (unsigned i = 0; i < size; i++) {
		sumValue += a[i];
	}
	return sumValue;
}

/* read() reads a stream for array size values.
 *
 * @param: istream in, the stream to be read from, double *a, the array for the values to be stored in, int size, the size of the array
 * @return: nothing.
 */
void read(istream& in, double *a, int size) {
	for(unsigned i = 0; i < size; i++) {
		in >> a[i];
	}
}

/* fill() fills a specified array with the values from a file.
 *
 * @param: istream in, the stream to be read from, double *&a, the array for the values to be stored in, int& numValues, the number of values to be read
 * @return: nothing.
 */
void fill(const string& fileName, double *&a, int &numValues) {
	ifstream fin(fileName.c_str());
	fin >> numValues;
	a = new double [numValues];
	for (int i = 0 ; i < numValues; i++) {
		fin >> a[i];
	}
};

/* resize() changes the size of a specified array.
 *
 * @param: double *&a, the array to be resized, int oldSize, the size of the array currently, int newSize, the size the array should be after
 * @return: nothing.
 */
void resize(double *&a, int oldSize, int newSize) {
	if (newSize > oldSize) {
		double * b = new double[newSize];
		for (int i = 0; i < oldSize; i++) {
			b[i] = *&a[i];
		}
		for (int i = oldSize; i < newSize; i++) {
			b[i] = 0;
		}
		delete [] *&a;
		*&a = b;
	};
	if (newSize < oldSize) {
		double * c = new double[newSize];
		for (int i = 0; i < newSize; i++) {
			c[i] = *&a[i];
		}
		delete [] *&a;
		*&a = c;
	}
}

/* concat() combines arrays into one.
 *
 * @param: a1, the first array to be added, int size1, the size of the first, a2, the second array, size2, the size of
 * the second array, double *&a3, the combined array name, int &size3, the size of the final array
 * @return: nothing.
 */
void concat(double *a1, int size1, double *a2, int size2, double *&a3, int &size3) {
	size3 = size1 + size2;
	double * b = new double[size3];
	for (int i = 0; i < size1; i++) {
		b[i] = a1[i];
	}
	for (int j = size1; j < size3; j++) {
		b[j] = a2[j-size1];
	}
	delete [] *&a3;
	*&a3 = b;
}


