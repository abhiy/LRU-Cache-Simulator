#include <iostream>
#include "l1.h"
#include "l2.h"
#include "l3.h"
using namespace std;

//Constructor
l2::l2(int size, int sets, int blockSize){
	_size = size;
	_sets = sets;
	_blocksize = blockSize;
	_ways = (size*1024)/(blockSize*sets);
}

//Called by l1 on a miss
void l2::access(string bitstring, cache *Cache){
 	int index = getIndex(bitstring);                 //Index to determine which set to go to
 	string tag = getTag(bitstring);			   	     //The tag

 	set<string>::iterator it;
 	it =_l2[index].find(tag);  						 //Indexing into the l1 cache and finding the tag
 	if(it != _l2[index].end() )                      //A cache hit! 
 	{
 		updateList(index, tag);						 //Make this line MRU
 		Cache->l1.insertL2_block(bitstring)          //Send block down to l1   
 	}
 	else  											 //A cache miss!
 	{
 		Cache->l3.Access(bitstring, Cache);      	 //Try to find the block in l2 
 	}
}


//Replaces the lru block with the new and returns the bitstring of that lru
string l2::runReplacement(int index, string tag){
	string _lru = lru[index].back();              //Find the lru block
	lru[index].pop_back();                          
	_l2[index].remove(mru);						  //Remove lru block from the set 
	_l2[index].insert(tag);                       //Insert tag into the set		
	lru[index].push_front(tag);					  //Insert tag into the lru list 

	string bitstring = getBitstring(int index, string tag);
	return bitstring;
}


//Called by l3 when it evicts a block
void l2::removeL3_block(string bitstring, cache *Cache){
	int index = getIndex(bitstring);
	string tag = getTag(bitstring);

	set<string>::iterator it;
 	it =_l2[index].find(tag);             
 	if(it != _l2[index].end())
 	{
 		_l2[index].erase(it);
 		lru[index].remove(tag);
 		Cache->l1.removeL2_block(bitstring, Cache);
 	}

 	//else do nothing
}

//Called by l3 to pass down the block missed
void l2::insertL3_block(string bitstring, cache *Cache){
	int index = getIndex(bitstring);
	string tag = getTag(bitstring);

	if(_l1[index].size() < _ways)
	{
		_l1[index].insert(tag);
		lru[index].push_front(tag);
	}
	else
	{
		string _bitstring = runReplacement(index, tag);
		Cache->l1.removeL2_block(_bitstring);
	}

	Cache->l1.insertL2_block(bitstring);
}

//Find tag, bring it to front
void l3::updateList(int index, string tag){
 	lru[index].erase(tag);
 	lru[index].push_front(tag);
}