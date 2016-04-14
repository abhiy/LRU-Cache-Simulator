#include <iostream>

#include "cahce.h"
#include "simulate.h"

using namespace std;

int main(){
	string fileName;
	cin >> fileName;

	cache Cache;

	Cache.simulate(fileName);

	cout << Cache.missCount << endl;
}