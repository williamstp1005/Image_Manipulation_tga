#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



struct Image {
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
	int totalPixels;
	unsigned char** pixelsArray;

	unsigned char blue;
	unsigned char green;
	unsigned char red;


	Image(ifstream& file) {
		ifstream& _file = file;
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
		totalPixels = width * height;
		pixelsArray = new unsigned char* [totalPixels];

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

	/*~Image() {
		for (int i = 0; i < totalPixels; i++) {
			delete[] pixelsArray[i];
		}
		delete[] pixelsArray;
	}*/

	void Print() {
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

	unsigned char subtractClamp(unsigned char minuend, unsigned char subtrahend) {
		unsigned char difference;
		if ((int)(minuend - subtrahend) < 0) {
			difference = 0;
		} else if ((int)(minuend - subtrahend) > 255) {
			difference = 255;
		} else {
			difference = minuend - subtrahend;
		}

		return difference;
	}

	unsigned char addClamp(unsigned char addend1, unsigned char addend2) {
		unsigned char sum;
		if ((int)(addend1 + addend2) < 0) {
			sum = 0;
		}
		else if ((int)(addend1 + addend2) > 255) {
			sum = 255;
		}
		else {
			sum = addend1 + addend2;
		}

		return sum;
	}

	unsigned char multiplyClamp(unsigned char multiplicand, unsigned char multiplier) {
		unsigned char product;
		if ((multiplicand * multiplier) > 255) {
			product = 255;
		} else {
			product = multiplicand * multiplier;
		}

		return product;
	}

	void outputHeaderSame(ofstream& outfile) {
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
	}

	void outputFileSameHeader(string filename) {
		ofstream outfile(filename, ios_base::binary);
		outputHeaderSame(outfile);

		for (int i = 0; i < totalPixels; i++) {
			outfile.write(reinterpret_cast<char*>(&pixelsArray[i][0]), 1);
			outfile.write(reinterpret_cast<char*>(&pixelsArray[i][1]), 1);
			outfile.write(reinterpret_cast<char*>(&pixelsArray[i][2]), 1);
		}

		outfile.close();
	}

	void multipliedWith(const Image& image) {
		for (int i = 0; i < this->totalPixels; i++) {
			int* multBuffer = new int[3];
			unsigned char* pixelMult = new unsigned char[3];

			for (int j = 0; j < 3; j++) {
				multBuffer[j] = (int)(((((float)image.pixelsArray[i][j] / 255) * ((float)this->pixelsArray[i][j] / 255)) * 255) + 0.5f);
				pixelMult[j] = (unsigned char)multBuffer[j];
			}

			this->pixelsArray[i] = pixelMult;
			
		}
	}

	void Minus(const Image& image) {
		for (int i = 0; i < this->totalPixels; i++) {
			unsigned char* pixelSub = new unsigned char[3];

			for (int j = 0; j < 3; j++) {
				pixelSub[j] = subtractClamp(this->pixelsArray[i][j], image.pixelsArray[i][j]);
			}

			this->pixelsArray[i] = pixelSub;
		}
	}

	void Plus(const Image& image) {
		for (int i = 0; i < this->totalPixels; i++) {
			unsigned char* pixelSub = new unsigned char[3];

			for (int j = 0; j < 3; j++) {
				pixelSub[j] = addClamp(this->pixelsArray[i][j], image.pixelsArray[i][j]);
			}

			this->pixelsArray[i] = pixelSub;
		}
	}

	void isScreenFor(const Image& image) {
		for (int i = 0; i < this->totalPixels; i++) {
			unsigned char* pixScr = new unsigned char[3];

			for (int j = 0; j < 3; j++) {
				pixScr[j] = (int)(((1 - ((1 - ((float)image.pixelsArray[i][j] / 255)) * (1 - ((float)this->pixelsArray[i][j] / 255)))) * 255) + 0.5f);
			}

			this->pixelsArray[i] = pixScr;
		}
	}

	void overlayedOn(const Image& image) {
		for (int i = 0; i < this->totalPixels; i++) {
			unsigned char* pixelMult = new unsigned char[3];

			for (int j = 0; j < 3; j++) {
				if (((float)image.pixelsArray[i][j] / 255) <= 0.5f) {
					pixelMult[j] = (unsigned char)(((((float)image.pixelsArray[i][j] / 255) * ((float)this->pixelsArray[i][j] / 255)) * 2 * 255) + 0.5f);
				} else {
					pixelMult[j] = (unsigned char)(((1 - (2 * (1 - ((float)image.pixelsArray[i][j] / 255)) * (1 - ((float)this->pixelsArray[i][j] / 255)))) * 255) + 0.5f);
				}
			}

			this->pixelsArray[i] = pixelMult;
		}
	}

	void addGreen() {
		for (int i = 0; i < this->totalPixels; i++) {
			this->pixelsArray[i][1] = addClamp(this->pixelsArray[i][1], 200);
		}
	}

	void channelScale() {
		for (int i = 0; i < this->totalPixels; i++) {
			this->pixelsArray[i][2] = multiplyClamp(this->pixelsArray[i][2], 4);
			this->pixelsArray[i][0] = multiplyClamp(this->pixelsArray[i][0], 0);
		}
	}

	void seperateChannels() {
		ofstream red("./output/part8_r.tga", ios_base::binary);
		ofstream green("./output/part8_g.tga", ios_base::binary);
		ofstream blue("./output/part8_b.tga", ios_base::binary);
		outputHeaderSame(blue);
		outputHeaderSame(green);
		outputHeaderSame(red);


		for (int i = 0; i < this->totalPixels; i++) {
			for (int j = 0; j < 3; j++) {
				blue.write(reinterpret_cast<char*>(&this->pixelsArray[i][0]), 1);
			}
			for (int j = 0; j < 3; j++) {
				green.write(reinterpret_cast<char*>(&this->pixelsArray[i][1]), 1);
			}
			for (int j = 0; j < 3; j++) {
				red.write(reinterpret_cast<char*>(&this->pixelsArray[i][2]), 1);
			}
		}

		red.close();
		green.close();
		blue.close();
	}

	void combineSelf_G_R(Image& green, Image& red) {
		for (int i = 0; i < this->totalPixels; i++) {
			this->pixelsArray[i][1] = green.pixelsArray[i][1];
			this->pixelsArray[i][2] = red.pixelsArray[i][2];
		}
	}

	void Rotate180() {
		unsigned char** reversedArray = new unsigned char* [this->totalPixels];
		for (int i = this->totalPixels - 1; i >= 0; i--) {
			int j = this->totalPixels - (i + 1);
			reversedArray[j] = this->pixelsArray[i];
		}

		for (int i = 0; i < this->totalPixels; i++) {
			this->pixelsArray[i] = reversedArray[i];
		}
		delete[] reversedArray;
	}
};