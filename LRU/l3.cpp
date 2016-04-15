#include <iostream>
#include "cache.h"

using namespace std;

l3::l3(int size, int sets, int blockSize){
	_size = size;
	_sets = sets;
	_blockSize = blockSize;
	_ways = (size*1024)/(blockSize*sets);

	missCount = 0;

	for(int i = 0; i < sets; i++){
		set<string> *myset = new set<string>;
		list<string> *mylist = new list<string>;
		_l3.push_back(*myset);
		lru.push_back(*mylist);
	}
}

//Called by l2 on a miss
void l3::access(string bitstring){
 	int index = getIndex(bitstring, _sets);      //Index to determine which set to go to
 	string tag = getTag(bitstring, _sets);		 //The tag
 	set<string>::iterator it;
 	it =_l3[index].find(tag);  						 //Indexing into the l1 cache and finding the tag
 	if(it != _l3[index].end() ){                      //A cache hit!
 		updateList(index, tag);	
 		//cout << "Hit" << endl;
 	}					   
 	else  											 //A cache miss!
 	{
 		//cout << "Miss" << endl;
 		//A trip down the memory lane
 		missCount++;
 		if(_l3[index].size() < _ways){
 			_l3[index].insert(tag);                  //Inserted the tag into the set
 			lru[index].push_front(tag);              //Inserted the tag into the lru list
 		}				
 		else
 		{
 			string _bitstring = runReplacement(index, tag);
 			Cache.L2->removeL3_block(_bitstring);
 		}
 	}	 

 	Cache.L2->insertL3_block(bitstring);       //Send block down to l2 
}

//Replaces the lru block with the new and returns the bitstring of that lru
string l3::runReplacement(int index, string tag){
	string _lru = lru[index].back();              //Find the lru block
	lru[index].pop_back();                          
	_l3[index].erase(_lru);						  //Remove lru block from the set 
	_l3[index].insert(tag);                       //Insert tag into the set		
	lru[index].push_front(tag);					  //Insert tag into the lru list 

	string bitstring = getBitstring(index, tag, _sets);
	return bitstring;
}

//Find tag, bring it to front
void l3::updateList(int index, string tag){
 	lru[index].remove(tag);
 	lru[index].push_front(tag);
}