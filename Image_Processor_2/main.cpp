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
        break;

        case 2: fileIn = "graycake.pgm";
        break;

        case 3: fileIn = "spheres.ppm";
        break;

        case 4: fileIn = "grayspheres.pgm";
        break;

        default: cout << "what are you an idiot?\n";
    }
    fin.close();
    Image m;
    m.readFromFile(fileIn);
    m.drawToConsole();
}
