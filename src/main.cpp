#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
using namespace std;

int main() {
	//part 1
	ifstream file1a("input/layer1.tga", ios_base::binary);
	ifstream file1b("input/pattern1.tga", ios_base::binary);
	Image image1a(file1a);
	image1a.Print();
	Image image1b(file1b);

	image1a.multipliedWith(image1b);
	image1a.outputFileSameHeader("output/part1.tga");

	
	//part 2
	ifstream file2a("input/car.tga", ios_base::binary);
	ifstream file2b("input/layer2.tga", ios_base::binary);
	Image image2a(file2a);
	Image image2b(file2b);

	image2a.Minus(image2b);
	image2a.outputFileSameHeader("output/part2.tga");


	//part 3
	ifstream file3a("./input/layer1.tga", ios_base::binary);
	ifstream file3b("./input/pattern2.tga", ios_base::binary);
	ifstream file3c("./input/text.tga", ios_base::binary);
	Image image3a(file3a);
	Image image3b(file3b);
	Image image3c(file3c);

	image3a.multipliedWith(image3b);
	image3a.isScreenFor(image3c);
	image3a.outputFileSameHeader("./output/part3.tga");
	

	//part 4
	ifstream file4a("./input/circles.tga", ios_base::binary);
	Image image4a(file4a);

	image4a.multipliedWith(image2b);
	image4a.Minus(image3b);
	image4a.outputFileSameHeader("./output/part4.tga");
	
	
	//part 5
	ifstream file5a("./input/layer1.tga", ios_base::binary);
	Image image5a(file5a);

	image5a.overlayedOn(image1b);
	image5a.outputFileSameHeader("./output/part5.tga");
	

	//part 6
	ifstream file6("./input/car.tga", ios_base::binary);
	Image image6(file6);

	image6.addGreen();
	image6.outputFileSameHeader("./output/part6.tga");
	

	//part 7
	ifstream file7("./input/car.tga", ios_base::binary);
	Image image7(file7);

	image7.channelScale();
	image7.outputFileSameHeader("./output/part7.tga");


	//part 8
	ifstream file8("./input/car.tga", ios_base::binary);
	Image image8(file8);

	image8.seperateChannels();
	

	//part 9
	ifstream file9a("./input/layer_blue.tga", ios_base::binary);
	ifstream file9b("./input/layer_green.tga", ios_base::binary);
	ifstream file9c("./input/layer_red.tga", ios_base::binary);
	Image image9a(file9a);
	Image image9b(file9b);
	Image image9c(file9c);


	image9a.combineSelf_G_R(image9b, image9c);
	image9a.outputFileSameHeader("./output/part9.tga");


	//part 10
	ifstream file10("./input/text2.tga", ios_base::binary);
	Image image10(file10);

	image10.Rotate180();
	image10.outputFileSameHeader("./output/part10.tga");
	
	return 0;
}

