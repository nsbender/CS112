/* tester.cpp runs the tests in this project
 * ...
 */

#include "MatrixTester.h"

void generateTestFile(unsigned SIZE);
//
//int main(int argc, char** argv) {
////	const unsigned MAX = 4096;
////	const unsigned MAX = 1024;
////	generateTestFile(MAX);
//	MatrixTester mt;
//	mt.runTests();
//}


/* function to generate a large Matrix datafile for testing
 * Parameter: SIZE, the number of rows and columns
 *              the test-matrix should have.
 * Postcondition: a SIZExSIZE matrix has been created
 *                 in a file named 'testFiles/SIZExSIZE.txt'.
 */

void generateTestFile(unsigned SIZE) {
        char buf[32];
        sprintf(buf, "testFiles/%dx%d.txt", SIZE, SIZE);
	ofstream fout(buf);
	assert( fout.is_open() );
	fout << SIZE << " " << SIZE << endl;
	for (unsigned i = 0; i < SIZE; i++) {
		for (unsigned j = 0; j < SIZE; j++) {
			fout << i*SIZE+j << '\t';
		}
		fout << '\n';
	}
	fout.close();
}
