#include <iostream>
#include "l1.h"
#include "func.h"

using namespace std;

l1::l1(int size, int sets, int blockSize){
	_size = size;
	_sets = sets;
	_blocksize = blockSize;
	_ways = (size*1024)/(blockSize*sets);
}

//Called by the processor to perform r/w
void l1::access(string addr, cache *Cache){
	string bitstring = getBits(addr);                //Convert hex string to binary string
 	int index = getIndex(bitstring);                 //Index to determine which set to go to
 	string tag = getTag(bitstring);			   	     //The tag

 	set<string>::iterator it;
 	it =_l1[index].find(tag);  						 //Indexing into the l1 cache and finding the tag
 	if(it != _l1[index].end() )                      //A cache hit! 
 	{
 		updateList(index, tag);						 //Make this line MRU
 	}
 	else  											 //A cache miss!
 	{
 		Cache->l2.Access(bitstring, Cache);      	 //Try to find the block in l2 
 	}
}

//Find tag, bring it to front
void l1::updateList(int index, string tag){
 	lru[index].erase(tag);
 	lru[index].push_front(tag);
}

//Called by l2 when it evicts a block
void l1::removeL2_block(string bitstring, cache *Cache){
	int index = getIndex(bitstring);
	string tag = getTag(bitstring);

	set<string>::iterator it;
 	it =_l2[index].find(tag);             
 	if(it != _l2[index].end())
 	{
 		_l2[index].erase(it);
 		lru[index].remove(tag);
 	}

 	//else do nothing
}

//Replaces the lru block with the new 
void l1::runReplacement(int index, string tag){
	string _lru = lru[index].back();              //Find the lru block
	lru[index].pop_back();                        //Remove it from the lru list
	_l1[index].remove(mru);						  //Remove it block from the set 
	_l1[index].insert(tag);                       //Insert tag into the set		
	lru[index].push_front(tag);					  //Insert tag into the lru list 
}

//Called by l2 to pass down the block missed
void l1::insertL2_block(string bitstring){
	int index = getIndex(bitstring);
	string tag = getTag(bitstring);

	if(_l1[index].size() < _ways)
	{
		_l1[index].insert(tag);
		lru[index].push_front(tag);
	}
	else
		runReplacement(index, tag);
}