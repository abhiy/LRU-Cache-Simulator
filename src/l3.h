#ifndef L3_H
#define L3_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

#include "cache.h"

using namespace std;

class l3{
private:
	int _size;
	int _ways;
	int _blockSize;
	int _sets;
	vector< set<string> > _l3(_sets);  
	vector<list<string> >lru(_sets);    		 
 public:
	l2(int size, int sets, int blockSize);
	void access(char ch, int addr, cache *Cache);
	string runReplacement(int index, string tag);
	updateList(int index, string tag);
};

#endif