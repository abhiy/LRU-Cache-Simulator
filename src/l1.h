#ifndef L1_H
#define L1_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

#include "cache.h"

using namespace std;

class l1{
private:
	int _size;
	int _ways;
	int _blockSize;
	int _sets;
	vector< set<string> > _l1(_sets);           //set < tag >
	vector<list<string> >lru(_sets);    		//For running LRU 
 public:
	l1(int size, int sets, int blockSize);		//Constructor
	access(char ch, int addr, cache *Cache);	//Called by the processor for r/w
	void runReplacement(int index, string tag)  //To run replacement algorithm in the given set, for inserting tag 
	updateList(int index, string tag);			//Find index in list, bring it to front (MRU)
	void removeL2_block(string bitstring, cache *Cache);
	void insertL2_block(string bitstring)
};

#endif

