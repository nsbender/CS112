/* Vec.h provides a simple vector class named Vec.
 * Student Name:
 * Date:
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
#include <stdexcept>
using namespace std;

typedef double Item;

class Vec {
public:
	Vec();
	Vec(unsigned size);
	Vec(const Vec& original);
	Vec& operator=(const Vec& original);
	unsigned getSize() const;
	void setItem(unsigned index, const Item& it);
	Item getItem(unsigned index) const;
	void setSize(unsigned newSize);
	virtual ~Vec();
	
private:
   unsigned mySize;
   Item *   myArray;
   friend class VecTester;
};


#endif /*VEC_H_*/
