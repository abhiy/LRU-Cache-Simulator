#include <iostream>

#include "cache.h"

using namespace std;

cache Cache;
int main(){
	string fileName;
	cin >> fileName;

	Cache.simulate(fileName);

	cout << "L3 Misses Per Kilo Instructions: " << (Cache.L3->missCount*1000)/(Cache.L1->insCount*1.0) << endl;
}