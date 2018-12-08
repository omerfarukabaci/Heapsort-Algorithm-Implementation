#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "Heap.cpp"

using namespace std;

int main() {
	Heap<int> numbers(MAX_HEAP);
	ifstream infile;
	ofstream outfile;
	string data;
	int counter = 0;
	clock_t t = clock();

	infile.open("numbers.csv");

	if (infile.good()) {
		while (getline(infile, data)) {
			numbers.insert(atoi(data.c_str()));
		}
	}

	infile.close();

	t = clock() - t;
	cout << "2.000.000 data inserted into heap in " << ((float)t) / CLOCKS_PER_SEC << " secs." << endl << endl;

	outfile.open("output.csv");

	t = clock();
	numbers.buildMaxHeap();
	t = clock() - t;
	cout << "Builded a Max-Heap in " << ((float)t) / CLOCKS_PER_SEC << " secs." << endl << endl;

	for (int i = 1; i <= 10; i++) {
		t = clock();
		cout << "STEP " << i << ": " << endl << endl;
		cout << "The height of the heap before STEP " << i << " is " << numbers.getTreeHeight() << endl;
		for (int j = 1; j <= 200000; j++) {
			outfile << numbers.extractMax() << endl;
		}
		t = clock() - t;
		cout << "Ran Extract-Max 200.000 times in " << ((float)t) / CLOCKS_PER_SEC << " secs." << endl << endl;
	}
	outfile.close();
	return 0;
}