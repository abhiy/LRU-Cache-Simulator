#ifndef L3_H
#define L3_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

#include "func.cpp"
#include "cache.h"

extern cache Cache;

using namespace std;

class l3{
private:
	int _size;
	int _ways;
	int _blockSize;
	int _sets;
	vector< set<string> >  _l3;  
	vector<list<string> > lru;    		 
 public:

 	unsigned int missCount;
	l3(int size, int sets, int blockSize);
	void access(string bitstring);
	string runReplacement(int index, string tag);
	void updateList(int index, string tag);
};

#endif