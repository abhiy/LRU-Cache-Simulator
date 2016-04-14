#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
#include "cache.h"
#include "math.h"

using namespace std;


string DecToBin(unsigned long number)
{
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";

    if ( number % 2 == 0 )
        return DecToBin(number / 2) + "0";
    else
        return DecToBin(number / 2) + "1";
}

string getBits(string addr){
	string bitstring;
	bitstring = DecToBin(addr);
		
	return bitstring;
}

int getIndex(string bitstring, cache *Cache){

}


#endif