#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



struct Header {
	char idLen;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLen;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
	int totalPixels = (int)width* (int)height;
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char** pixelsArray = new unsigned char* [totalPixels];


	Header(ifstream& file) {
		file.read(&idLen, 1);
		file.read(&colorMapType, 1);
		file.read(&dataTypeCode, 1);
		file.read(reinterpret_cast<char*>(&colorMapOrigin), 2);
		file.read(reinterpret_cast<char*>(&colorMapLen), 2);
		file.read(&colorMapDepth, 1);
		file.read(reinterpret_cast<char*>(&xOrigin), 2);
		file.read(reinterpret_cast<char*>(&yOrigin), 2);
		file.read(reinterpret_cast<char*>(&width), 2);
		file.read(reinterpret_cast<char*>(&height), 2);
		file.read(&bitsPerPixel, 1);
		file.read(&imageDescriptor, 1);

		for (int i = 0; i < totalPixels; i++) {
			unsigned char* pixel = new unsigned char[3];

			file.read(reinterpret_cast<char*>(&blue), 1);
			file.read(reinterpret_cast<char*>(&green), 1);
			file.read(reinterpret_cast<char*>(&red), 1);
			pixel[0] = blue;
			pixel[1] = green;
			pixel[2] = red;

			pixelsArray[i] = pixel;

		}
	}

	void print() {
		cout << "idLen             " << (int)idLen << endl
			<< "colorMapType      " << (int)colorMapType << endl
			<< "dataTypeCode      " << (int)dataTypeCode << endl
			<< "colorMapOrigin    " << colorMapOrigin << endl
			<< "colorMapLen       " << colorMapLen << endl
			<< "colorMapDepth     " << (int)colorMapDepth << endl
			<< "xOrigin           " << xOrigin << endl
			<< "yOrigin           " << yOrigin << endl
			<< "width             " << width << endl
			<< "height            " << height << endl
			<< "bitsPerPixel      " << (int)bitsPerPixel << endl
			<< "imageDescriptor   " << (int)imageDescriptor << endl;
	}

	void outputTestFile() {
		ofstream outfile("test.tga", ios_base::binary);
		outfile.write(&idLen, 1);
		outfile.write(&colorMapType, 1);
		outfile.write(&dataTypeCode, 1);
		outfile.write(reinterpret_cast<char*>(&colorMapOrigin), 2);
		outfile.write(reinterpret_cast<char*>(&colorMapLen), 2);
		outfile.write(&colorMapDepth, 1);
		outfile.write(reinterpret_cast<char*>(&xOrigin), 2);
		outfile.write(reinterpret_cast<char*>(&yOrigin), 2);
		outfile.write(reinterpret_cast<char*>(&width), 2);
		outfile.write(reinterpret_cast<char*>(&height), 2);
		outfile.write(&bitsPerPixel, 1);
		outfile.write(&imageDescriptor, 1);

		for (int i = 0; i < totalPixels; i++) {
			outfile.write(reinterpret_cast<char*>(&pixelsArray[i][0]), 1);
			outfile.write(reinterpret_cast<char*>(&pixelsArray[i][1]), 1);
			outfile.write(reinterpret_cast<char*>(&pixelsArray[i][2]), 1);
		}
	}

};
