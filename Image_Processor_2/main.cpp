#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "Image.h"
using namespace std;

int main()
{
    SetConsoleTitle("Image Processor 2.0");

    string fileIn;
    string format;                                                                                      ///Format of the image
    int width = 0;                                                                                          ///amount of columns
    int height = 0;                                                                                         ///amount of rows
    int brightness = 0;

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
        case 1: fileIn = "cake.ppm";
        fin.open(fileIn);
        fin >> format >> width >> height >> brightness;
        break;

        case 2: fileIn = "graycake.pgm";
        fin.open(fileIn);
        fin >> format >> width >> height >> brightness;
        break;

        case 3: fileIn = "spheres.ppm";
        fin.open(fileIn);
        fin >> format >> width >> height >> brightness;
        break;

        case 4: fileIn = "grayspheres.pgm";
        fin.open(fileIn);
        fin >> format >> width >> height >> brightness;
        break;

        default: cout << "Pick a valid choice?\n";
    }
    fin.close();
    Image m(width, height, brightness, format, fileIn);
    m.readFromFile(fileIn);
    m.drawToConsole();
}
