#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "l1.h"
#include "l2.h"
#include "l3.h"

using namespace std;

class cache{
public:
	l1 *L1;
	l2 *L2;
	l3 *L3;
	void simulate(string filename);
	unsigned long int missCount;
	cache();
};

#endif	
