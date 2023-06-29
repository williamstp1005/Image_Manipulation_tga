#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;

int main() {
	ifstream layer("car.tga", ios_base::binary);
	//ifstream pattern("pattern1.tga", ios_base::binary);
	Header firstFile(layer);
	//Header secondFile(pattern);
	firstFile.print();	
	firstFile.outputTestFile();

	cout << "done" << endl;
	return 0;
}

