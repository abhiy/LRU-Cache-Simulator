#include <iostream>
#include "l3.h"
using namespace std;

l3::l3(int size, int sets, int blockSize){
	_size = size;
	_sets = sets;
	_blocksize = blockSize;
	_ways = (size*1024)/(blockSize*sets);
}

//Called by l2 on a miss
void l3::access(string bitstring, cache *Cache){
 	int index = getIndex(bitstring, Cache->L3);      //Index to determine which set to go to
 	string tag = getTag(bitstring, Cache->L3);		 //The tag

 	set<string>::iterator it;
 	it =_l3[index].find(tag);  						 //Indexing into the l1 cache and finding the tag
 	if(it != _l3[index].end() )                      //A cache hit!
 		updateList(index, tag);						 //Make this line MRU  
 	else  											 //A cache miss!
 	{
 		//A trip down the memory lane
 		Cache->missCount++;
 		if(_l3[index].size() < _ways){
 			_l3[index].insert(tag);                  //Inserted the tag into the set
 			lru[index].push_front(tag);              //Inserted the tag into the lru list
 		}				
 		else
 		{
 			string _bitstring = runReplacement(index, tag);
 			Cache->L2.removeL3_block(_bitstring);
 		}
 	}	 

 	Cache->L2.insertL3_block(bitstring, Cache)       //Send block down to l2 
}

//Replaces the lru block with the new and returns the bitstring of that lru
string l3::runReplacement(int index, string tag){
	string _lru = lru[index].back();              //Find the lru block
	lru[index].pop_back();                          
	_l3[index].remove(mru);						  //Remove lru block from the set 
	_l3[index].insert(tag);                       //Insert tag into the set		
	lru[index].push_front(tag);					  //Insert tag into the lru list 

	string bitstring = getBitstring(int index, string tag);
	return bitstring;
}

//Find tag, bring it to front
void l3::updateList(int index, string tag){
 	lru[index].erase(tag);
 	lru[index].push_front(tag);
}