#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <string>
#include <stream>
#include <iomanip>

#include "l1.h"
#include "l2.h"
#include "l3.h"


class cache{
private:
	l1 L1;
	l2 L2;
	l3 L3;
public:
	void simulate(string filename);
	unsigned long int missCount;
	//l1(size(in KB), sets, blockSize)
	cache(): L1(32, 64, 64), L2(256, 512, 64), L3(2048, 2048, 64), missCount(0) {}
};

void cache::simulate(string filename){
	ifstream inputfile(filename);
	unsigned long addr;
	string delim;
	while(!inputfile.eof()){
		inputfile >> hex >> addr;
		inputfile >> delim;
		this->L1.access(addr);
	}
}
#endif

