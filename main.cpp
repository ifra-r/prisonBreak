#include <iostream>
#include <fstream>
#include <string>
#include "Grid.h"
using namespace std;

int testCases;

int main() {
	int Tmaps = 0;
	Grid map;
	ifstream rdr("data.txt");
	rdr >> Tmaps;
	for (int i = 0; i < Tmaps; i++) {
		cout << "map #" << i+1 << ":\n";
		map.load(rdr);
		map.print();
		map.prisonSolver();
		cout << endl;
	}
	return 0;
}