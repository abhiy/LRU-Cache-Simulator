#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <list>

#include "func.h"

using namespace std;

class l1;
class l2;
class l3;
class cache;

extern cache Cache;
class cache{
public:
	l1 *L1;
	l2 *L2;
	l3 *L3;
	void simulate(string filename);
	unsigned long int missCount;
	cache();
};


class l1{
private:
	int _size;
	int _ways;
	int _blockSize;
	int _sets;
	vector< set<string> > _l1;           //set < tag >
	vector<list<string> > lru;    		//For running LRU 
 public:
 	unsigned int insCount;
 	l2 *L2;
	l1(int size, int sets, int blockSize);		//Constructor
	void access(unsigned long addr);	            //Called by the processor for r/w
	void runReplacement(int index, string tag);  //To run replacement algorithm in the given set, for inserting tag 
	void updateList(int index, string tag);			//Find tag in list, bring it to front (MRU)
	void removeL2_block(string bitstring);
	void insertL2_block(string bitstring);
};

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

class l3{
private:
	int _size;
	int _ways;
	int _blockSize;
	int _sets;
	vector< set<string> >  _l3;  
	vector<list<string> > lru;    		 
 public:
 	unsigned int insCount;
 	unsigned int missCount;
	l3(int size, int sets, int blockSize);
	void access(string bitstring);
	string runReplacement(int index, string tag);
	void updateList(int index, string tag);
};

#endif	
