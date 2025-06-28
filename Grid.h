#pragma once
#include <fstream>
#include <vector>
using namespace std;

struct Position {
	int x, y;
};

class Grid
{
private:
	int** Vs;
	int rows, cols;
	Position topLeft, bottomRight, Prisoner;
	int  canEscape = 0;

	void allocate();
	void deAllocate();

	void findTopLeft();
	void findBottomRight();
	void findPrisoner();
	void assigning_Positions();

	void RemFirstIndex(vector <Position> &memArr);
	bool isBoundary(vector <Position> memArr, int index);
	bool isIndexBoundary(int r, int c);

	bool isAlreadyOut();
	void displayResults(int option);
public:
	Grid();
	Grid(int r, int c);
	void setRows(int r);
	void setCols(int c);

	void load(ifstream& rdr);
	void print();
	void prisonSolver();
};

