#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
#include "math.h"

using namespace std;

string DecToBin(unsigned long number);
int BinToDec(string number);
string getBits(unsigned long addr);
int getIndex(string bitstring, int sets);
string getTag(string bitstring, int sets);
string getBitstring(int index, string tag, int sets);

#endif