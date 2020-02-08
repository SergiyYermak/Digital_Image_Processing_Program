#define _WIN32_WINNT 0x500
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include "Image.h"
using namespace std;

///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Image::Image()
{
    ImageArr = new Pixel[0];
    head = nullptr;
    currentPix = nullptr;
    currentFirstCol = nullptr;
    currentCol = 0;
    currentRow = 0;

    currentNumOfPixels = 0;
    maxColumns = 0;
    maxRows = 0;
    maxBrightness = 0;
    format = "";
    fileName = "";
}
Image::Image(const int columns, const int rows, const int brightness, const string formt, const string fName)
{
    ImageArr = new Pixel[columns * rows];
    head = nullptr;
    currentPix = nullptr;
    currentFirstCol = nullptr;
    currentCol = 0;
    currentRow = 0;

    currentNumOfPixels = 0;
    maxColumns = columns;
    maxRows = rows;
    maxBrightness = brightness;
    format = formt;
    fileName = fName;
}
///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Image::~Image(){}

///Getter & Setters----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
///Getters
int Image::getColumns() const
{
    return maxColumns;
}
int Image::getRows() const
{
    return maxRows;
}
int Image::getBrightness() const
{
    return maxBrightness;
}
string Image::getFormat() const
{
    return format;
}
string Image::getFileName() const
{
    return fileName;
}

///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Image::addPixel(Pixel p)
{
    ImageArr[currentNumOfPixels] = p;
    ///If very first pixel, set to head, set to currentFirstCol, and currentPix;
    if(currentCol == 0 && currentRow == 0)
    {
        head = &p;
        currentPix = &p;
        currentFirstCol = &p;
        currentCol++;
    }
    ///If max amount of pixels are in a row, add the next pixel to the next row.
    else if(currentCol == maxColumns)
    {
        ///Step 1 and 2
        (*currentFirstCol).setDown(p);
        p.setUp(*currentFirstCol);

        ///Step 3 and 4
        (*(*currentFirstCol).getRight()).setDownLeft(p);                                   ///ERROR IS HERE
        p.setUpRight(*((*currentFirstCol).getRight()));

        ///Update current information
        currentCol = 0;
        currentRow++;
        currentPix = (*currentFirstCol).getDown();
        currentFirstCol = (*currentFirstCol).getDown();
    }
    else
    {
        ///Step 1 and 2
        (*currentPix).setRight(p);
        p.setLeft(*currentPix);

        ///Step 3 and 4
        if((*currentPix).getUp() != nullptr)
        {
            (*(*currentPix).getUp()).setDownRight(*((*currentPix).getRight()));
            (*(*currentPix).getRight()).setUpLeft(*((*currentPix).getUp()));
        }

        ///Step 5 and 6
        if((*currentPix).getUpRight() != nullptr)
        {
            (*(*currentPix).getUpRight()).setDown(*((*currentPix).getRight()));
            (*(*currentPix).getRight()).setUp(*((*currentPix).getUpRight()));
            ///Step 7 and 8
            if((*(*currentPix).getUpRight()).getRight() != nullptr)
            {
                (*(*(*currentPix).getUpRight()).getRight()).setDownLeft(*((*currentPix).getRight()));
                (*(*currentPix).getRight()).setUpRight(*((*(*currentPix).getUpRight()).getRight()));
            }
        }
        ///Step 9 and 10
        currentCol++;
        currentPix = &p;
    }
    currentNumOfPixels++;
}
void Image::readFromFile(const string fileIn)
{
    ifstream fin;
    fin.open(fileIn.c_str());

    fin >> format >> maxColumns >> maxRows >> maxBrightness;
    cout << "Image Resolution: " << maxRows << ", " << maxColumns << endl
         << "Image Format: " << format << endl;

    if(format == "P3")
    {
        int red, green, blue;
        for(int i = 0; i < (maxRows * maxColumns); i++)
        {
            fin >> red >> green >> blue;
            Pixel p(red,green,blue);
            addPixel(p);
        }
    }
    else
    {
        int white;
        for(int i = 0; i < (maxRows * maxColumns); i++)
        {
                fin >> white;
                Pixel p(white);
                addPixel(p);
                cerr << "Added pixel: " << currentNumOfPixels << endl;
        }
    }
    fin.close();
}

void Image::drawToConsole()
{
    ///Draws ppm or pgm file onto the console window
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);

    int currentC = 0;
    int currentR = 0;
    Pixel currentP = *head;
    Pixel currentFirst = *head;

    if(getFormat() == "P3")
    {
        for(int row = 0; row < getRows(); row++)
        {
            for(int col = 0; col < getColumns(); col++)
            {
                COLORREF COLOR = RGB(currentP.getPixelRed(),
                                     currentP.getPixelGreen(),
                                     currentP.getPixelBlue());
                SetPixel(hdc, (col + 500), row, COLOR);

                ///update current
                if(currentC == maxColumns-1)
                {
                    currentC = 0;
                    currentR++;
                    currentP = *(currentFirst.getDown());
                    currentFirst = *(currentFirst.getDown());
                }
                else
                {
                    currentC++;
                    currentP = *(currentP.getLeft());
                }
             }
        }
        ReleaseDC(hwnd, hdc);
        DeleteDC(hdc);
    }
    else
    {
        for(int row = 0; row < getRows(); row++)
        {
            for(int col = 0; col < getColumns(); col++)
            {
                COLORREF COLOR = RGB(currentP.getPixelWhite(),
                                     currentP.getPixelWhite(),
                                     currentP.getPixelWhite());
                SetPixel(hdc, (col + 500), row, COLOR);

                ///update current
                if(currentC == maxColumns-1)
                {
                    currentC = 0;
                    currentR++;
                    currentP = *(currentFirst.getDown());
                    currentFirst = *(currentFirst.getDown());
                }
                else
                {
                    currentC++;
                    currentP = *(currentP.getLeft());
                }
             }
        }
        ReleaseDC(hwnd, hdc);
        DeleteDC(hdc);
    }
}

