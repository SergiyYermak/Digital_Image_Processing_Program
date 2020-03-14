#include <fstream>
#include <iomanip>
#include "IntensityMachine.h"
#include "HistogramMachine.h"
using namespace std;

int main()
{
    //SetConsoleTitle("Image Processor");

    string fileIn;
    string format;
    int width;
    int height;
    int brightness;

    int fileChoice;
    cout << "Choose the image to edit: " << endl
             << "1. cake.ppm" << endl
             << "2. graycake.pgm" << endl
             << "3. spheres.ppm" << endl
             << "4. grayspheres.pgm" << endl;
    cin >> fileChoice;
    ifstream fin;

    fin.open("fadedcircle.pgm");
    fin >> format >> width >> height >> brightness;
    fileIn = "fadedcircle.pgm";
    Image fadedCircle(width, height, brightness, format, fileIn);
    fadedCircle.readFromFile(fileIn);

    switch(fileChoice)
    {
        case 1: fin.open("cake.ppm");
        fin >> format >> width >> height >> brightness;
        fileIn = "cake.ppm";
        break;

        case 2: fin.open("graycake.pgm");
        fin >> format >> width >> height >> brightness;
        fileIn = "graycake.pgm";
        break;

        case 3: fin.open("spheres.ppm");
        fin >> format >> width >> height >> brightness;
        fileIn = "spheres.ppm";
        break;

        case 4: fin.open("grayspheres.pgm");
        fin >> format >> width >> height >> brightness;
        fileIn = "grayspheres.pgm";
        break;

        default: cout << "Wrong input was received\n";
    }
    fin.close();

    Image original(width, height, brightness, format, fileIn);
    original.readFromFile(fileIn);

    IntensityMachine im;
    Image darkerOrginal(im.powerTransformation(original, 3.0));

    HistogramMachine hm;
    Image equalized(hm.histogramEqualizeImage(darkerOrginal));

    Image matched(hm.histogramMatching(darkerOrginal, equalized));

    darkerOrginal.writeToFile("testGrayOutput1.pgm");
    equalized.writeToFile("testGrayOutput2.pgm");
    matched.writeToFile("testGrayOutput3.pgm");
}
