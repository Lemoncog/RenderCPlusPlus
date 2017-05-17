#include "tgaimage.h"
#include <math.h>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void box(TGAImage &image, int xStart, int yStart, int xEnd, int yEnd);
void line(TGAImage &image, int xStart, int yStart, int xEnd, int yEnd);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);

    line(image, 0, 0, 85, 25);

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

void line(TGAImage &image, int xStart, int yStart, int xEnd, int yEnd) {
    int xDiff = abs(xStart - xEnd);
    int yDiff = abs(yStart - yEnd);

    float lineLength = sqrt((xDiff*xDiff)+(yDiff*yDiff));
    float xStep = xDiff/lineLength;
    float yStep = yDiff/lineLength;

    for(int s = 0; s < lineLength; s++) {
        image.set(xStart+(xStep*s), yStart+(yStep*s), white);
    }
}

void box(TGAImage &image, int xStart, int yStart, int xEnd, int yEnd) {
    int xDiff = abs(xStart - xEnd);
    int yDiff = abs(yStart - yEnd);

    for(int x = 0; x < xDiff; x++) {
        for(int y = 0; y < yDiff; y++) {
            image.set(xStart+x, yStart+y, white);
        }
    }
}

