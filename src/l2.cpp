#include <iostream>
#include "l2.h"
using namespace std;

//Constructor
l2::l2(int size, int sets, int blockSize){
	_size = size;
	_sets = sets;
	_blockSize = blockSize;
	_ways = (size*1024)/(blockSize*sets);

	for(int i = 0; i < sets; i++){
		set<string> *myset = new set<string>;
		list<string> *mylist = new list<string>;
		_l2.push_back(*myset);
		lru.push_back(*mylist);
	}
}

//Called by l1 on a miss
void l2::access(string bitstring){
 	int index = getIndex(bitstring, _sets);                 //Index to determine which set to go to
 	string tag = getTag(bitstring, _sets);			   	     //The tag

 	set<string>::iterator it;
 	it =_l2[index].find(tag);  						 //Indexing into the l1 cache and finding the tag
 	if(it != _l2[index].end() )                      //A cache hit! 
 	{
 		updateList(index, tag);						 //Make this line MRU
 		Cache->L1->insertL2_block(bitstring, Cache);         //Send block down to l1   
 	}
 	else  											 //A cache miss!
 	{
 		Cache->L3->access(bitstring, Cache);      	   //Try to find the block in l2 
 	}
}


//Replaces the lru block with the new and returns the bitstring of that lru
string l2::runReplacement(int index, string tag){
	string _lru = lru[index].back();              //Find the lru block
	lru[index].pop_back();                          
	_l2[index].erase(_lru);						  //Remove lru block from the set 
	_l2[index].insert(tag);                       //Insert tag into the set		
	lru[index].push_front(tag);					  //Insert tag into the lru list 

	string bitstring = getBitstring(index, tag, _sets);
	return bitstring;
}


//Called by l3 when it evicts a block
void l2::removeL3_block(string bitstring){
	int index = getIndex(bitstring, _sets);
	string tag = getTag(bitstring, _sets);

	set<string>::iterator it;
 	it =_l2[index].find(tag);             
 	if(it != _l2[index].end())
 	{
 		_l2[index].erase(it);
 		lru[index].remove(tag);
 		Cache->L1->removeL2_block(bitstring);
 	}

 	//else do nothing
}

//Called by l3 to pass down the block missed
void l2::insertL3_block(string bitstring){
	int index = getIndex(bitstring, _sets);
	string tag = getTag(bitstring, _sets);

	if(_l2[index].size() < _ways)
	{
		_l2[index].insert(tag);
		lru[index].push_front(tag);
	}
	else
	{
		string _bitstring = runReplacement(index, tag);
		Cache->L1->removeL2_block(_bitstring);
	}

	Cache->L1->insertL2_block(bitstring);
}

//Find tag, bring it to front
void l2::updateList(int index, string tag){
 	lru[index].remove(tag);
 	lru[index].push_front(tag);
}