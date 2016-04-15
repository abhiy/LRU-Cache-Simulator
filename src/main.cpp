#include <iostream>

#include "cache.h"

using namespace std;

cache Cache;
int main(){
	string fileName;
	cin >> fileName;

	Cache.simulate(fileName);

	cout << Cache.missCount << endl;
}