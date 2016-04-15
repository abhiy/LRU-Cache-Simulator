#ifndef L1_H
#define L1_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

#include "func.cpp"
#include "l2.h"
#include "cache.h"

extern cache Cache;

using namespace std;

class l1{
private:
	int _size;
	int _ways;
	int _blockSize;
	int _sets;
	vector< set<string> > _l1;           //set < tag >
	vector<list<string> > lru;    		//For running LRU 
 public:
 	l2 *L2;
	l1(int size, int sets, int blockSize);		//Constructor
	void access(unsigned long addr);	            //Called by the processor for r/w
	void runReplacement(int index, string tag);  //To run replacement algorithm in the given set, for inserting tag 
	void updateList(int index, string tag);			//Find tag in list, bring it to front (MRU)
	void removeL2_block(string bitstring);
	void insertL2_block(string bitstring);
};

#endif

