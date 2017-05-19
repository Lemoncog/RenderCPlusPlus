#include <iostream>
#include "geometry.h"
#include "tgaimage.h"
#include "model.h"
#include <math.h>

void box(TGAImage &image, int xStart, int yStart, int xEnd, int yEnd);
void line(TGAImage &image, Vec2f start, Vec2f end);
void line(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, const char * argv[]) {
    
    Model model("obj/african_head/african_head.obj");
    
    std::cout << "loaded model, " << model.nfaces() << " faces\n";
    
    Vec3f vec(1.0f, 0.0f, 0.0f);

    float width = 100;
    float height = 100;
    TGAImage image(width, height, TGAImage::RGB);
    
    line(image, Vec2f(width, height), Vec2f(0.f, 0.f), white);
    line(image, Vec2f(10.f, 0), Vec2f(width, 95.f), red);

    line(image, Vec2f(0.f, height), Vec2f(width, 0.f), white);
    line(image, Vec2f(width, 0), Vec2f(0.f, 95.f), red);

    line(image, Vec2f(50.f, height), Vec2f(50.f, 0.f), white);
    line(image, Vec2f(55.f, 0), Vec2f(55.f, height), red);

    line(image, Vec2f(0.f, 50.f), Vec2f(width, 50.f), white);
    line(image, Vec2f(width, 55.f), Vec2f(0.f, 55.f), red);

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    bool done = image.write_tga_file("image.tga");
    
    std::cout << "Hello, World!\n" << vec << "\n" << ( done ? "done" : "failed" ) << "\n";
    
    return 0;
}

void line(TGAImage &image, Vec2f start, Vec2f end, TGAColor color) {
    int xDiff = end.x- start.x;
    int yDiff = end.y - start.y;

    float lineLength = abs(sqrt((xDiff*xDiff)+(yDiff*yDiff)));
    float xStep = xDiff/lineLength;
    float yStep = yDiff/lineLength;

    for(int s = 0; s < lineLength; s++) {
        image.set(start.x+(xStep*s), start.y+(yStep*s), color);
    }
}

void line(TGAImage &image, Vec2f start, Vec2f end) {
    line(image, start, end);
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
