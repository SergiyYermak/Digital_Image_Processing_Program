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

        default: cout << "Wrong input?\n";
    }
    fin.close();

    Image m(width, height, brightness, format, fileIn);
    m.readFromFile(fileIn);
    IntensityMachine im;
    m = im.powerTransformation(m, 0.5);

    HistogramMachine hm;
    Image n(m);
    n = hm.histogramEqualizeImage(m);


    if(format == "P3")
    {
        m.writeToFile("testColorOutput.ppm");

    }
    else
        m.writeToFile("testGrayOutputM.pgm");
        n.writeToFile("testGrayOutputN.pgm");
}
