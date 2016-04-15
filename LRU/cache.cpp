#include <iostream>
#include "cache.h"

using namespace std;


void cache::simulate(string filename){
	ifstream inputfile(filename);
	unsigned long addr;
	string delim;
	while(!inputfile.eof()){
		inputfile >> hex >> addr;
		inputfile >> delim;
		this->L1->access(addr);
	}
}

//l1(size(in KB), sets, blockSize)
cache::cache(){
	L1 = new l1(32, 64, 64);
	L2 = new l2(256, 512, 64);
	L3 = new l3(2048, 2048, 64);

	missCount = 0;
}