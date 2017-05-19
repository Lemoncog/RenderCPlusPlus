#include <iostream>
#include "geometry.h"
#include "tgaimage.h"
#include "model.h"
#include <math.h>

using namespace std;

void box(TGAImage &image, int xStart, int yStart, int xEnd, int yEnd);
void triangle(TGAImage &image, Vec2f a, Vec2f b, Vec2f c,TGAColor color);
void triangleFilled(TGAImage &image, Vec2f a, Vec2f b, Vec2f c,TGAColor color);
void triangleSweepSOHCAHTOA(TGAImage &image, Vec2f a, Vec2f b, Vec2f c,TGAColor color);
void triangleBCeriFormula(TGAImage &image, Vec2f a, Vec2f b, Vec2f c, TGAColor color);
void triangleBaryFormula(TGAImage &image, Vec2f v1, Vec2f v2, Vec2f v3, TGAColor color);
void line(TGAImage &image, Vec2f start, Vec2f end);
void line(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);
void lineB(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);
void lineStep1(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);
void lineStep2(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);
void lineStep3(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);
void lineStep4(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);
void lineStep5(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);
void lineA(TGAImage &image, Vec2f start, Vec2f end, TGAColor color);
void wireFrame(TGAImage &image, Model& model);

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor blue  = TGAColor(0, 255, 255, 255);

int main(int argc, const char * argv[]) {
    
    Model model("obj/african_head/african_head.obj");
    
    std::cout << "loaded model, " << model.nfaces() << " faces\n";
    
    Vec3f vec(1.0f, 0.0f, 0.0f);

    float width = 1200;
    float height = 900;
    TGAImage image(width, height, TGAImage::RGB);

//    triangleFilled(image, Vec2f(100, 100), Vec2f(700, 700), Vec2f(500, 100), WHITE);
    wireFrame(image, model);

//    line(image, Vec2f(width, height), Vec2f(0.f, 0.f), WHITE);
//    line(image, Vec2f(10.f, 0), Vec2f(width, 95.f), red);
//    line(image, Vec2f(35.f, 35), Vec2f(70.f, 25.f), WHITE);

//    line(image, Vec2f(0.f, height), Vec2f(width, 0.f), WHITE);
//    line(image, Vec2f(width, 0), Vec2f(0.f, 95.f), red);
//
//    line(image, Vec2f(50.f, height), Vec2f(50.f, 0.f), WHITE);
//    line(image, Vec2f(55.f, 0), Vec2f(55.f, height), red);
//
//    line(image, Vec2f(0.f, 50.f), Vec2f(width, 50.f), WHITE);
//    line(image, Vec2f(width, 55.f), Vec2f(0.f, 55.f), red);

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    bool done = image.write_tga_file("image.tga");
    
    std::cout << "Hello, World!\n" << vec << "\n" << ( done ? "done" : "failed" ) << "\n";
    
    return 0;
}

Vec3f normalize(Vec3f vec, int width, int height) {
    return Vec3f(vec.x * width, vec.y * height, vec.z);
}

Vec3f center(Vec3f vec, int width, int height) {
    return Vec3f(vec.x+(width/2), vec.y+(height/2), vec.z);
}

void wireFrame(TGAImage &image, Model& model) {
    int width = image.get_width();
    int height = image.get_height();

    for(int i = 0;i < model.nfaces(); i++) {
        vector<int> vector = model.face(i);

        TGAColor color = TGAColor(arc4random()*255, arc4random()*255, arc4random()*255, 255);

        Vec3f pointA = normalize(model.vert(vector[0]), width, height);
        Vec3f pointB = normalize(model.vert(vector[1]), width, height);
        Vec3f pointC = normalize(model.vert(vector[2]), width, height);

        pointA = center(pointA, width, height);
        pointB = center(pointB, width, height);
        pointC = center(pointC, width, height);

        Vec2f pointA2(pointA.x, pointA.y);
        Vec2f pointB2(pointB.x, pointB.y);
        Vec2f pointC2(pointC.x, pointC.y);

        triangleFilled(image, pointA2, pointB2, pointC2, WHITE);
    }
}

void triangleFilled(TGAImage &image, Vec2f a, Vec2f b, Vec2f c,TGAColor color) {
    triangleBCeriFormula(image, a, b, c, color);
    triangle(image, a, b, c, color);
}

Vec2f calculateDiff(Vec2f from, Vec2f to) {
    return Vec2f(to.x - from.x, to.y - from .y);
}

float calculateLength(Vec2f from, Vec2f to) {
    int xDiffA = to.x-from.x;
    int yDiffA = to.y-from.y;
    return abs(sqrt((xDiffA*xDiffA)+(yDiffA*yDiffA)));
}

int calculateX(int y, Vec2f v1, Vec2f v2) {
    Vec2f diff = calculateDiff(v1, v2);
    int m = (diff.y/diff.x);
    int b = v1.y - (m * v1.x);
    return (y - (b))/m;
}

void triangleBaryFormula(TGAImage &image, Vec2f v1, Vec2f v2, Vec2f v3, TGAColor color) {

}

void triangleBCeriFormula(TGAImage &image, Vec2f v1, Vec2f v2, Vec2f v3, TGAColor color) {

    float minY = 0;
    if(v1.y < v2.y && v1.y < v3.y) {
        minY = v1.y;
    }

    if(v2.y < v3.y && v2.y < v1.y) {
        minY = v2.y;
    }

    if(v3.y < v2.y && v3.y < v1.y) {
        minY = v3.y;
    }

    //900 needs to be max Y
    int maxY = 900;
    for(int y = minY; y < maxY; y++) {
        int minX = calculateX(y, v1, v2);
        int maxX = calculateX(y, v2, v3);

        for(int b = minX; b < maxX; b++) {
            image.set(b, y, red);
        }
    }
}

void triangleSweepSOHCAHTOA(TGAImage &image, Vec2f a, Vec2f b, Vec2f c, TGAColor color) {
    //GIVEN UP
    line(image, a, b, color);

    float aSide = calculateLength(a, b);
    float bSide = calculateLength(b, c);
    float cSide = calculateLength(c, a);

    //BODMAS
    float blip = ((((aSide*2) + (cSide*2)) - (bSide*2))/2)*aSide*cSide;

//    a = arccos((x2 + z2 - y2)/2xz)
//    b = arccos((y2 + z2 - x2)/2yz)
//    c = arccos((x2 + y2 - z2)/2xy)
}

void triangle(TGAImage &image, Vec2f a, Vec2f b, Vec2f c,TGAColor color) {
    line(image, a, b, color);
    line(image, b, c, color);
    line(image, c, a, color);
}

void line(TGAImage &image, Vec2f start, Vec2f end, TGAColor color) {
    lineB(image, start, end, color);
}

void lineStep1(TGAImage &image, Vec2f start, Vec2f end, TGAColor color) {
    float startX = start.x;
    float startY = start.y;

    float endX = end.x;
    float endY = end.y;

    double stepIncr = .01;

    for (float step=0.; step < 1.; step+=stepIncr) {


        int x = startX * (1. - step) + endX * step;
        int y = startY*(1.-step) + endY*step;
        image.set(x, y, color);
    }
}

void lineStep2(TGAImage &image, Vec2f start, Vec2f end, TGAColor color) {
    int x0 = start.x;
    int x1 = end.x;
    int y0 = start.y;
    int y1 = end.y;
    
    for (int x=x0; x <= x1; x++) {
        float t = (x-x0)/(float)(x1-x0);
        int y = y0*(1.-t) + y1*t;
        image.set(x, y, color);
    }
}

void lineStep3(TGAImage &image, Vec2f start, Vec2f end, TGAColor color) {
    int x0 = start.x;
    int x1 = end.x;
    int y0 = start.y;
    int y1 = end.y;

    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) { // if the line is steep, we transpose the image
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) { // make it left−to−right
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float) (x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        if (steep) {
            image.set(y, x, color); // if transposed, de−transpose
        } else {
            image.set(x, y, color);
        }
    }
}

void lineStep4(TGAImage &image, Vec2f start, Vec2f end, TGAColor color) {
    int startX = start.x;
    int endX = end.x;
    int startY = start.y;
    int endY = end.y;

    bool steep = false;
    if (std::abs(startX-endX)<std::abs(startY-endY)) {
        std::swap(startX, startY);
        std::swap(endX, endY);
        steep = true;
    }
    if (startX>endX) {
        std::swap(startX, endX);
        std::swap(startY, endY);
    }

    int xDiff = endX-startX;
    int yDiff = endY-startY;

    float derror = std::abs(yDiff/float(xDiff));
    float error = 0;

    int y = startY;
    for (int x=startX; x<=endX; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error += derror;
        if (error>.5) {
            y += (endY>startY?1:-1);
            error -= 1.;
        }
    }
}

void lineStep5(TGAImage &image, Vec2f start, Vec2f end, TGAColor color) {
    int startX = start.x;
    int endX = end.x;
    int startY = start.y;
    int endY = end.y;

    bool steep = false;
    if (std::abs(startX-endX)<std::abs(startY-endY)) {
        std::swap(startX, startY);
        std::swap(endX, endY);
        steep = true;
    }
    if (startX>endX) {
        std::swap(startX, endX);
        std::swap(startY, endY);
    }

    int xDiff = endX-startX;
    int yDiff = endY-startY;

    float derror2 = std::abs(yDiff*2);
    float error2 = 0;

    int y = startY;
    for (int x=startX; x<=endX; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2>.5) {
            y += (endY>startY?1:-1);
            error2 -= xDiff*2;
        }
    }
}

/**
 * My line.
 * Attempt B
 */
void lineB(TGAImage &image, Vec2f start, Vec2f end, TGAColor color) {
    int xDiff = end.x - start.x;
    int yDiff = end.y - start.y;

    float lineLength = abs(sqrt((xDiff*xDiff)+(yDiff*yDiff)));

    float xStep = xDiff/lineLength;
    float yStep = yDiff/lineLength;

    float derror = abs(float(yDiff)/float(xDiff));
    float error = 0;

    for(int s = 0; s < lineLength; s++) {
        image.set(start.x+(xStep*s), start.y+(yStep*s), color);
    }

    image.set(start.x, start.y, blue);
    image.set(end.x, end.y, blue);
}

void line(TGAImage &image, Vec2f start, Vec2f end) {
    line(image, start, end, red);
}

void box(TGAImage &image, int xStart, int yStart, int xEnd, int yEnd) {
    int xDiff = abs(xStart - xEnd);
    int yDiff = abs(yStart - yEnd);

    for(int x = 0; x < xDiff; x++) {
        for(int y = 0; y < yDiff; y++) {
            image.set(xStart+x, yStart+y, WHITE);
        }
    }
}
