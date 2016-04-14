#ifndef L2_H
#define L2_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

#include "cache.h"

using namespace std;

class l2{
private:
	int _size;
	int _ways;
	int _blockSize;
	int _sets;
	vector< map<string, string> > _l2(_sets);   //map < index, tag >
	vector<list<string> >lru(_sets);    		//For running LRU 
 public:
	l2(int size, int sets, int blockSize);
	access(char ch, int addr, cache *Cache);
	string runReplacement(int index, string tag);
	updateList(int set, string index);
	void removeL3_block(string bitstring, cache *Cache);
};

#endif