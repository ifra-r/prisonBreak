#include "Grid.h"
#include <iostream>
#include <fstream>

using namespace std;

Grid::Grid():rows(0),cols(0) {
	Vs = nullptr;
	topLeft = { 0,0 }, bottomRight = { 0,0 }, Prisoner = { 0,0 };
}
Grid::Grid(int r, int c) :rows(r),cols(c) {
	topLeft = { 0,0 }, bottomRight = { 0,0 }, Prisoner = { 0,0 };
	Vs = nullptr;
}


void Grid::allocate() {
	//cout << "Allocating\n";
	Vs = new int* [rows] {};
	for (int i = 0; i < rows; i++) {
		Vs[i] = new int [cols] {};
	}
}


void Grid::deAllocate() {
	//cout << "\nDe-Allocating\n";
	for (int i = 0; i < rows; i++) {
		delete[] Vs[i];
	}
	delete[] Vs;
}

void Grid::load(ifstream& rdr) {
	rdr >> rows >> cols;
	if (Vs != nullptr) {
		deAllocate();
	}
	allocate();

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			rdr >> Vs[r][c];
		}
	}
}

void Grid::print() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			cout << Vs[r][c] << " ";
		}
		cout << endl;
	}
}


void Grid::setCols(int r) {
	rows = r;
}
void Grid::setRows(int c) {
	cols = c;
}


void Grid::findTopLeft() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (Vs[r][c] == 1) {
				topLeft = { r, c };
				//cout << "top: " << topLeft.x << "," << topLeft.y << endl;
				return;
			}
		}
	}
}
void Grid::findBottomRight() {
	for (int r = rows-1; r >= 0; r--) {
		for (int c = cols-1; c >= 0; c--) {
			if (Vs[r][c] == 1) {
				bottomRight = { r, c };
				//cout << "\nbottom: " << bottomRight.x << "," << bottomRight.y << endl;
				return;
			}
		}
	}
}
void Grid::findPrisoner() {
	for (int r = rows - 1; r >= 0; r--) {
		for (int c = cols - 1; c >= 0; c--) {
			if (Vs[r][c] == 2) {
				Prisoner = { r, c };
				//cout << "2 is at: " << Prisoner.x << "," << Prisoner.y << endl;
				return;
			}
		}
	}
}

void Grid::assigning_Positions() {
	findTopLeft();
	findBottomRight();
	findPrisoner();
}

bool Grid::isBoundary(vector <Position> memArr, int ind) {
	int r = memArr[ind].x, c = memArr[ind].y;
	if (r >= 0 && r < rows && c >= 0 && c < cols) {
		if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) {
			return true;
		}
	}
	else {
		cerr << "\nout of bounds..";
	}
	return false;
}

bool Grid::isIndexBoundary(int r, int c) {
	if (r >= 0 && r < rows && c >= 0 && c < cols) {
		if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) {
			return true;
		}
	}
	else {
		cerr << "\nout of bounds..";
	}
	return false;
}

void Grid::displayResults(int option) {
	switch (option) {
	case -1:
		cout << "Prisoner is already out" << endl;
		break;
	case 1:
		cout << "Prisoner can escape" << endl;
		break;
	default:
		cout << "Imprisoned for life" << endl;
		break;
	}
}

void Grid::RemFirstIndex(vector <Position> &memArr) {
	if (!memArr.empty()) {
		if (isBoundary(memArr, 0)) {
			canEscape = 1;
		}
		Vs[memArr[0].x][memArr[0].y] = 3;
		memArr.erase(memArr.begin());
	}
	else {
		cerr << "remove 2: out of bounds." << endl;
	}
}

bool Grid::isAlreadyOut() {
	int tx = topLeft.x, ty = topLeft.y,
		bx = bottomRight.x, by = bottomRight.y,
		px = Prisoner.x, py = Prisoner.y;
	if (px<tx || py<ty || px>bx || py>by) {
		canEscape = -1;
		return true;
	}
	return false;
}

void Grid::prisonSolver() {

	assigning_Positions();
	canEscape = 0;

	if (!isAlreadyOut()) {

		vector <Position> memArr;
		memArr.push_back(Prisoner);
		while (!memArr.empty()) {

			int x = memArr[0].x, y = memArr[0].y;
			//int surroundingsR, surroundingsC;
			if (isBoundary(memArr, 0)) {
				canEscape = 1;
				Vs[memArr[0].x][memArr[0].y] = 3;
				displayResults(canEscape);
				return;
			}
			if (Vs[x - 1][y] == 0) {
				memArr.push_back({ x - 1,y });
			}
			if (Vs[x][y - 1] == 0) {
				memArr.push_back({ x,y - 1 });
			}
			if (Vs[x][y + 1] == 0) {
				memArr.push_back({ x,y + 1 });
			}
			if (Vs[x + 1][y] == 0) {
				memArr.push_back({ x + 1,y });
			}

			RemFirstIndex(memArr);
		}
	}
	displayResults(canEscape);

}