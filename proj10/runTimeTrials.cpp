/* runTimeTrials.cpp uses MatrixTimer to time different Matrix operations.
 * Joel C. Adams, for CS 112 at Calvin College
 * Copyright Joel C. Adams 2009.  All Rights Reserved.
 */

#include "MatrixTimer.h"
#include "Matrix.h"
#include <cstdlib>
#include <fstream>
using namespace std;

string buildLogFileName(unsigned  numTrials);

int main() {
	unsigned numTrials = 10;	      // number of trials to average
	string logFileName = buildLogFileName(numTrials);
	omp_set_num_threads(16);
	MatrixTimer matrixTimer(numTrials, logFileName);
	matrixTimer.run();
}

/* utility method to build unique log-file names
 * Parameter: numTrials, the number of trials to be performed
 * Return: a unique file name incorporating numTrials
 */
string buildLogFileName(unsigned  numTrials) {
	string emptyString = "";
	char buf[16];
	sprintf(buf, "%02d", numTrials);
	string prefix = emptyString + "trials-" + buf;
	string result = "";
	ifstream fin;
	unsigned count = 0;
	while ( true ) {
		count++;
		sprintf(buf,"-%03d.txt", count);
		result = prefix + buf;
		fin.open(result.c_str());
		if ( !fin.is_open() ) break;
		fin.close();
	}
	fin.close();
	return result;
}

