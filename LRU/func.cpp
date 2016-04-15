#include "func.h"

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

int BinToDec(string number)
{	
    int result = 0, pow = 1;
    for ( int i = number.length() - 1; i >= 0; --i, pow <<= 1 )
        result += (number[i] - '0') * pow;
    return result;
}

string getBits(unsigned long addr){
	string bitstring;
	bitstring = DecToBin(addr);
	int diff = 32 - bitstring.size();
	if(diff > 0){
		for(int i = 0; i < diff; i++)
		{
			bitstring.insert(bitstring.begin(), '0');
		}
	}	
	return bitstring;
}

int getIndex(string bitstring, int sets){
	int num =log2(sets);
	return BinToDec(bitstring.substr(29-num, num));
}

string getTag(string bitstring, int sets){
	int num =log2(sets);
	return bitstring.substr(0, 28-num);
}

string getBitstring(int index, string tag, int sets){
	int num = log2(sets);
	string s1 = DecToBin(index);
	int diff = num - s1.size();
	if(diff > 0){
		for(int i = 1; i <= diff + 3; i++)
		{
			s1.insert(s1.end(), '0');
		}
	}

	return tag + s1;
}
