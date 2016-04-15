#ifndef L2_H
#define L2_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

#include "func.cpp"
#include "cache.h"

extern cache Cache;

using namespace std;

class l2{
private:
	int _size;
	int _ways;
	int _blockSize;
	int _sets;
	vector< set<string> > _l2;   //map < index, tag >
	vector<list<string> > lru;    		//For running LRU 
 public:
	l2(int size, int sets, int blockSize);
	void access(string bitstring);
	string runReplacement(int index, string tag);
	void updateList(int set, string index);
	void removeL3_block(string bitstring);
	void insertL3_block(string bitstring);
};

#endif