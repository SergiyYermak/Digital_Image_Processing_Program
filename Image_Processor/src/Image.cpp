//#define _WIN32_WINNT 0x500
//#include <windows.h>
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
    image = new Vector[3];
    for(int i = 0; i < 3; i++)
    {
        Vector v(3);
        image[i] = v;
    }
    numColumns = 3;
    numRows = 3;
    maxBrightness = 255;
    format = "";
    fileName = "";
}
Image::Image(const int columns, const int rows, const int brightness, const string form, const string fName)
{
    image = new Vector[columns];
    for (int i = 0; i < columns; i++)
    {
        Vector v(rows);
        image[i] = v;
    }
    numColumns = columns;
    numRows = rows;
    maxBrightness = brightness;
    format = form;
    fileName = fName;
}
///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Image::~Image(){}
///Setters & Getters---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
///Getters
int Image::getColumns() const
{
    return numColumns;
}
int Image::getRows() const
{
    return numRows;
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
Pixel Image::getImagePixel(const int row, const int column)
{
    Vector v = image[column];
    return v.getVectorPixel(row);
}
Vector Image::getRowVector(const int row)
{
    Vector v(getColumns());
    for(int i = 0; i < getColumns(); i++)
    {
        Pixel p = getImagePixel(row,i);
        v.setVectorPixel(i,p);
    }
    return v;
}
Vector Image::getColumnVector(const int column)
{
    return image[column];
}
///Setters
void Image::setImagePixel(const int column, const int row, Pixel input)
{
    Vector v = image[column];
    v.setVectorPixel(row, input);
}
void Image::setRowVector(const int row, Vector &v)
{
    for(int i = 0; i < getColumns(); i++)
    {
        Pixel a = v.getVectorPixel(i);
        setImagePixel(i,row,a);
    }
}
void Image::setColumnVector(const int column, Vector &v)
{
    image[column] = v;
}
///Operators-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Image::operator = (Image obj)
{
    for(int row = 0; row < obj.getRows(); row++)
    {
        for(int col = 0; col < obj.getColumns(); col++)
        {
            Pixel p = obj.getImagePixel(row, col);
            setImagePixel(col, row, p);
        }
    }
}
///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Image::writeToFile()
{
    string fileNamed = getFileName();
    if(getFormat() == "P3")
    {
        ofstream fout;
        fout.open(fileNamed.c_str());
        fout << getFormat() << endl
             << getColumns() << " " << getRows() << endl
             << getBrightness() << endl;
        for(int i = 0; i < getRows(); i++)
        {
            for(int j = 0; j < getColumns(); j++)
            {
                Pixel p = getImagePixel(i,j);
                fout << p.getPixelRed() << " " << p.getPixelGreen() << " " << p.getPixelBlue() << " ";
            }
            fout << endl;
        }
        fout.close();
    }
    else
    {
        ofstream fout;
        fout.open(fileNamed.c_str());
        fout << getFormat() << endl
             << getColumns() << " " << getRows() << endl
             << getBrightness() << endl;
        for(int i = 0; i < getRows(); i++)
        {
            for(int j = 0; j < getColumns(); j++)
            {
                Pixel p = getImagePixel(i,j);
                fout << p.getPixelWhite() << " ";
            }
            fout << endl;
        }
        fout.close();
    }
}
void Image::writeToFile(std::string fileIn)
{
    string fileNamed = fileIn;
    if(getFormat() == "P3")
    {
        ofstream fout;
        fout.open(fileNamed.c_str());
        fout << getFormat() << endl
             << getColumns() << " " << getRows() << endl
             << getBrightness() << endl;
        for(int i = 0; i < getRows(); i++)
        {
            for(int j = 0; j < getColumns(); j++)
            {
                Pixel p = getImagePixel(i,j);
                fout << p.getPixelRed() << " " << p.getPixelGreen() << " " << p.getPixelBlue() << " ";
            }
            fout << endl;
        }
        fout.close();
    }
    else
    {
        ofstream fout;
        fout.open(fileNamed.c_str());
        fout << getFormat() << endl
             << getColumns() << " " << getRows() << endl
             << getBrightness() << endl;
        for(int i = 0; i < getRows(); i++)
        {
            for(int j = 0; j < getColumns(); j++)
            {
                Pixel p = getImagePixel(i,j);
                fout << p.getPixelWhite() << " ";
            }
            fout << endl;
        }
        fout.close();
    }
}
void Image::readFromFile(const string fileIn)
{
    string format;
    int width;
    int height;
    int brightness;
    ifstream fin;
    fin.open(fileIn.c_str());

    fin >> format >> width >> height >> brightness;
    cout << "Image Resolution: " << height << ", " << width << endl
         << "Image Format: " << format << endl;

    if(format == "P3")
    {
        int red, green, blue;
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                fin >> red >> green >> blue;
                Pixel p(red,green,blue);
                setImagePixel(j,i,p);
            }
        }
    }
    else
    {
        int white;
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                fin >> white;
                Pixel p;
                p.setPixelWhite(white);
                setImagePixel(j,i,p);
            }
        }
    }
    fin.close();
}
Image Image::rotateImage(int choice)
{
    if(choice == 1)
    {
        ///ClockWise
        Image n(getRows(),getColumns(),getBrightness(),getFormat(), getFileName());
        for(int i = 0; i < getRows(); i++)
        {
            Vector v = getRowVector(i);
            int column = n.getColumns()-1-i;
            n.setColumnVector(column,v);
        }
        return n;
    }
    if(choice == 2)
    {
        ///Counter clockwise
        Image n (getRows(),getColumns(),getBrightness(),getFormat(), getFileName());
        for(int i = 0; i < getRows(); i++)
        {
            Vector v = getRowVector(i);
            n.setColumnVector(i,v);
        }
        return n;
    }
    if(choice == 3)
    {
        ///180
        Image n(getColumns(),getRows(), getBrightness(),getFormat(), getFileName());
        ///even
        if(getRows()%2 == 0)
        {
           for(int i = 0; i < getRows()/2; i++)
           {
               Vector top = getRowVector(i).reverseVector();
               Vector bottom = getRowVector(getRows()-1-i).reverseVector();
               n.setRowVector(i,bottom);
               n.setRowVector(getRows()-1-i, top);
           }
        }
        ///odd
        else
        {
            for(int i = 0; i < getRows()/2; i++)
            {
                Vector top = getRowVector(i).reverseVector();
                Vector bottom = getRowVector(getRows()-1-i).reverseVector();
                n.setRowVector(i,bottom);
                n.setRowVector(getRows()-1-i, top);
            }
            int middleIndex = ((getRows()-1)/2);
            Vector middleV = getRowVector(middleIndex).reverseVector();
            n.setRowVector(middleIndex, middleV);
        }
        return n;
    }
}
void Image::adjustBrightness(const int factor)
{
    for(int i = 0; i < getRows(); i++)
    {
        for(int j = 0; j < getColumns(); j++)
        {
            Pixel p = getImagePixel(i,j);
            p.adjustPixelBrightness(factor,getBrightness());
            setImagePixel(j,i,p);
        }
    }
}
void Image::addWatermark(const int brightness, const int letterWidth, const int letterHeight, const int firstRow, const int firstCol)
{
    ///Setting up pixel p brightness
    Pixel p;
    ///Setting up the spacing between letters
    int space = 10;
    if(getFormat() == "P3")
    {
        if(brightness <= getBrightness() && brightness >= 0)
        {
            p.setPixelRed(brightness);
            p.setPixelGreen(brightness);
            p.setPixelBlue(brightness);
        }
        else if(brightness > getBrightness())
        {
            p.setPixelRed(getBrightness());
            p.setPixelGreen(getBrightness());
            p.setPixelBlue(getBrightness());
        }
        else
        {
            p.setPixelRed(0);
            p.setPixelGreen(0);
            p.setPixelBlue(0);
        }
    }
    else
    {
        if(brightness <= getBrightness() && brightness >= 0)
        {
            p.setPixelWhite(brightness);
        }
        else if(brightness > getBrightness())
        {
            p.setPixelWhite(getBrightness());
        }
        else
        {
            p.setPixelWhite(0);
        }
    }
    ///H
    ///first column in H
    for(int i = firstRow; i < (firstRow + letterHeight); i++)
    {
        setImagePixel(firstCol,i,p);
    }
    ///second column in H
    for(int i = firstRow; i < (firstRow + letterHeight); i++)
    {
        int col = firstCol+letterWidth-1;
        setImagePixel(col,i,p);
    }
    ///row in H
    for(int j = firstCol + 1; j < (firstCol + letterWidth); j++)
    {
        int row = firstRow + ((letterHeight-1)/2);
        setImagePixel(j,row, p);
    }

    ///I
    ///column in I
    int col = firstCol + letterWidth + space;
    for(int i = firstRow; i < (firstRow + letterHeight); i++)
    {
        setImagePixel(col,i,p);
    }

    ///L
    ///column in first L
    col += space;
    for(int i = firstRow; i < (firstRow + letterHeight); i++)
    {

        setImagePixel(col,i,p);
    }
    ///row in first L
    for(int j = col; j < (col + letterWidth); j++)
    {
        setImagePixel(j,firstRow+letterHeight-1,p);
    }

    ///L
    ///column in second L
    col = col + space + letterWidth;
    for(int i = firstRow; i < (firstRow + letterHeight); i++)
    {
        setImagePixel(col,i,p);
    }
    ///row in second L
    for(int j = col; j < (col + letterWidth); j++)
    {
        setImagePixel(j,firstRow+letterHeight-1,p);
    }
}
Image Image::stretchImage(const int widthFactor, const int heightFactor)
{
    ///stretch width wise
    Image a((getColumns()* widthFactor), getRows(), getBrightness(), getFormat(), getFileName());
    for(int i = 0; i < getColumns(); i++)
    {
        Vector v = getColumnVector(i);
        int k = i * widthFactor;
        for(int j = i * widthFactor; j < k + widthFactor; j++)
        {
            a.setColumnVector(j, v);
        }
    }

    ///stretch height wise
    Image b(a.getColumns(), (getRows()* heightFactor), getBrightness(), getFormat(), getFileName());
    for(int i = 0; i < getRows(); i++)
    {
        Vector v = a.getRowVector(i);
        int k = i * heightFactor;
        for(int j = i * heightFactor; j < k + heightFactor; j++)
        {
            b.setRowVector(j,v);
        }
    }
    return b;
}
void Image::convertToGray()
{
    for(int row = 0; row < getRows(); row++)
    {
        for(int col = 0; col < getColumns(); col++)
        {
            Pixel p = getImagePixel(row, col);
            int intensity = (p.getPixelRed() * 0.3)+(p.getPixelGreen() * 0.6)+(p.getPixelBlue() * 0.1);
            p.setPixelWhite(intensity);
            setImagePixel(col, row, p);
        }
        format = "P2";
        fileName = "ConvertedToGray.pgm";
    }
}
/*
void Image::drawToConsole()
{
    ///Draws ppm or pgm file onto the console window
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);

    if(getFormat() == "P3")
    {
        for(int row = 0; row < getRows(); row++)
        {
            for(int col = 0; col < getColumns(); col++)
            {
                COLORREF COLOR = RGB(getImagePixel(row, col).getPixelRed(),
                                     getImagePixel(row, col).getPixelGreen(),
                                     getImagePixel(row, col).getPixelBlue());
                SetPixel(hdc, (col + 500), row, COLOR);
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
                COLORREF COLOR = RGB(getImagePixel(row, col).getPixelWhite(),
                                     getImagePixel(row, col).getPixelWhite(),
                                     getImagePixel(row, col).getPixelWhite());
                SetPixel(hdc, (col + 500), row, COLOR);
            }
        }
        ReleaseDC(hwnd, hdc);
        DeleteDC(hdc);
    }
}
*/
///Intensity Transformations-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Image::negative()
{
    int intensity = getBrightness();

    if(getFormat() == "P3")
    {
        for(int c = 0; c < getColumns(); c++)
        {
            for(int r = 0; r < getRows(); r++)
            {
                Pixel p = getImagePixel(r,c);
                int negativeR = intensity - p.getPixelRed();
                int negativeG = intensity - p.getPixelGreen();
                int negativeB = intensity - p.getPixelBlue();
                p.setPixelRed(negativeR);
                p.setPixelGreen(negativeG);
                p.setPixelBlue(negativeB);
                setImagePixel(c,r,p);
            }
        }

    }
    else
    {
        for(int c = 0; c < getColumns(); c++)
        {
            for(int r = 0; r < getRows(); r++)
            {
                Pixel p = getImagePixel(r,c);
                int negative = intensity - p.getPixelWhite();
                p.setPixelWhite(negative);
                setImagePixel(c,r,p);
            }
        }
    }
}
void Image::logTransformation()
{
    if(getFormat()=="P3")
    {
        for(int col = 0; col < getColumns(); col++)
        {
            for(int row = 0; row < getRows(); row++)
            {
                Pixel p = getImagePixel(row, col);
                int newR = (getBrightness()/log(1+getBrightness()))*log(1+p.getPixelRed());
                int newG = (getBrightness()/log(1+getBrightness()))*log(1+p.getPixelGreen());
                int newB = (getBrightness()/log(1+getBrightness()))*log(1+p.getPixelBlue());
                p.setPixelRed(newR);
                p.setPixelGreen(newG);
                p.setPixelBlue(newB);
                setImagePixel(col,row,p);
            }
        }
    }
    else
    {
        for(int col = 0; col < getColumns(); col++)
        {
            for(int row = 0; row < getRows(); row++)
            {
                Pixel p = getImagePixel(row, col);
                int newW = (getBrightness()/log(1+getBrightness()))*log(1+p.getPixelWhite());
                p.setPixelWhite(newW);
                setImagePixel(col,row,p);
            }
        }
    }
}
void Image::powerTransformation(const double gamma)
{
    if(getFormat()=="P3")
    {
        for(int col = 0; col < getColumns(); col++)
        {
            for(int row = 0; row < getRows(); row++)
            {
                Pixel p = getImagePixel(row, col);
                int newR = (pow(((double)p.getPixelRed()/(double)getBrightness()),gamma)) * getBrightness();
                int newG = (pow(((double)p.getPixelGreen()/(double)getBrightness()),gamma)) * getBrightness();
                int newB = (pow(((double)p.getPixelBlue()/(double)getBrightness()),gamma)) * getBrightness();
                p.setPixelRed(newR);
                p.setPixelGreen(newG);
                p.setPixelBlue(newB);
                setImagePixel(col, row, p);
            }
        }
    }
    else
    {
        for(int col = 0; col < getColumns(); col++)
        {
            for(int row = 0; row < getRows(); row++)
            {
                Pixel p = getImagePixel(row, col);
                int newW = (pow(((double)p.getPixelWhite()/(double)getBrightness()),gamma)) * getBrightness();
                p.setPixelWhite(newW);
                setImagePixel(col, row, p);
            }
        }
    }
}
void Image::contrastStretch(const int r1, const int s1, const int r2, const int s2)
{
    for(int row = 0; row < getRows(); row++)
    {
        for(int col = 0; col < getColumns(); col++)
        {
            Pixel p = getImagePixel(row, col);

            p.setPixelWhite(calcContrast(r1, r2, s1, s2, p.getPixelWhite()));

            setImagePixel(col, row, p);
        }
    }
}
int Image::calcContrast(const int r1, const int r2, const int s1, const int s2, const double original)
{
    double slope;
    int output = -1;
    if(original <= r1)
    {
        slope = s1/r1;
        output = slope * original;
    }
    else if(r1 > original && original <= r2)
    {
        if(s1 == s2)
        {
            output = s2;
        }
        ///do not need check for r1 == r2 as it will be calculated by the first if
        else
        {
            slope = (s2 - s1)/(r2 - r1);
            int value = original - r1;
            output = s1+ (value * slope);
        }
    }
    else if(original > r2)
    {
        slope = (getBrightness() - s2)/(getBrightness() - r2);
        int value = original - r2;
        output = s2 + (value * slope);
    }
    return output;
}
void Image::intensityLevelSlicing(const int a, const int b, const bool showOther)
{
    if(showOther == false)
    {
        for(int col = 0; col < getColumns(); col++)
        {
            for(int row = 0; row < getRows(); row++)
            {
                Pixel p = getImagePixel(row, col);
                if(p.getPixelWhite() >= a && p.getPixelWhite() <= b) //in range
                {
                    p.setPixelWhite(getBrightness()/2);
                    setImagePixel(col, row, p);
                }
                else
                {
                    p.setPixelWhite(0);
                    setImagePixel(col, row, p);
                }

            }
        }
    }
    else
    {
        for(int col = 0; col < getColumns(); col++)
        {
            for(int row = 0; row < getRows(); row++)
            {
                Pixel p = getImagePixel(row, col);
                if(p.getPixelWhite() >= a && p.getPixelWhite() <= b) //in range
                {
                    p.setPixelWhite(getBrightness()/1.25);
                    setImagePixel(col, row, p);
                }
            }
        }
    }
}
Image Image::bitPlaneSlice(const int bitPlaneNum)
{
    Image bitPlaneImage(getColumns(), getRows(), 1, "P2", getFileName());
    ///for all the pixels
    for(int row = 0; row < getRows(); row++)
    {
        for(int col = 0; col < getColumns(); col++)
        {
            ///grab a pixel
            Pixel p = getImagePixel(row, col);
            ///convert its intensity to binary
            string binary = intToBinary(p.getPixelWhite());
            ///check the bitplane number
            if(bitPlaneNum == 8)
            {
                if(binary.at(0)=='1')
                    p.setPixelWhite(1);
                else
                    p.setPixelWhite(0);
            }
            if(bitPlaneNum == 7)
            {
                if(binary.at(1)=='1')
                    p.setPixelWhite(1);
                else
                    p.setPixelWhite(0);
            }
            if(bitPlaneNum == 6)
            {
                if(binary.at(2)=='1')
                    p.setPixelWhite(1);
                else
                    p.setPixelWhite(0);
            }
            if(bitPlaneNum == 5)
            {
                if(binary.at(3)=='1')
                    p.setPixelWhite(1);
                else
                    p.setPixelWhite(0);
            }
            if(bitPlaneNum == 4)
            {
                if(binary.at(4)=='1')
                    p.setPixelWhite(1);
                else
                    p.setPixelWhite(0);
            }
            if(bitPlaneNum == 3)
            {
                if(binary.at(5)=='1')
                    p.setPixelWhite(1);
                else
                    p.setPixelWhite(0);
            }
            if(bitPlaneNum == 2)
            {
                if(binary.at(6)=='1')
                    p.setPixelWhite(1);
                else
                    p.setPixelWhite(0);
            }
            if(bitPlaneNum == 1)
            {
                if(binary.at(7)=='1')
                    p.setPixelWhite(1);
                else
                    p.setPixelWhite(0);
            }
            bitPlaneImage.setImagePixel(col, row, p);
        }
    }
    return bitPlaneImage;
}
Image Image::bitPlaneReconstruction(int a, int b)
{
    Image reconstructedImage(getColumns(), getRows(), getBrightness(), getFormat(), getFileName());
    for(int i = a; i >= b; i--)
    {
        reconstructedImage.addBitPlane(bitPlaneSlice(i), i);
    }
    return reconstructedImage;
}
void Image::addBitPlane(Image bitPlaneSlice, int bitLevel)
{
    for(int row = 0; row < getRows(); row++)
    {
        for(int col = 0; col < getColumns(); col++)
        {
            Pixel p = getImagePixel(row, col);
            int currentIntensity = p.getPixelWhite();
            int intensity = 0;
            if(bitPlaneSlice.getImagePixel(row, col).getPixelWhite() > 0)
                intensity = pow(2,(bitLevel-1));
            p.setPixelWhite(currentIntensity + intensity);
            setImagePixel(col, row, p);
        }
    }
}
string Image::intToBinary(int input)
{
    string binary = "00000000";
    if(input >= 128)
    {
        binary[0] = '1';
        input -= 128;
    }
    if(input >= 64)
    {
        binary[1] = '1';
        input -= 64;
    }
    if(input >= 32)
    {
        binary[2] = '1';
        input -= 32;
    }
    if(input >= 16)
    {
        binary[3] = '1';
        input -= 16;
    }
    if(input >= 8)
    {
        binary[4] = '1';
        input -= 8;
    }
    if(input >= 4)
    {
        binary[5] = '1';
        input -= 4;
    }
    if(input >= 2)
    {
        binary[6] = '1';
        input -= 2;
    }
    if(input >= 1)
    {
        binary[7] = '1';
        input -= 1;
    }
    return binary;
}
///Histogram Processing------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Image::makeEqualizedHistogram()
{
    int intensity = getBrightness();
    int nSubK[intensity] = { 0 };
    for(int col = 0; col < getColumns(); col++)
    {
        for(int row = 0; row < getRows(); row++)
        {
            int currentValue = nSubK[getImagePixel(row, col).getPixelWhite()];
            int newValue = currentValue + 1;
            nSubK[getImagePixel(row, col).getPixelWhite()] = newValue;
        }
    }
    int MN = getRows() * getColumns();
    double pSubR[intensity];
    for(int i = 0; i < intensity; i++)
    {
        pSubR[i] = (((double)nSubK[i])/((double)MN));
    }
    double sSubK[intensity];
    for(int i = 0; i < intensity; i++)
    {
        sSubK[i] = round(pSubR[i] * (intensity - 1));
    }
    equalizedHistogram = new double[intensity];
    for(int i = 0; i < intensity; i++)
    {
        int value = 0;
        for(int k = 0; k < intensity; k++)
        {
            if(sSubK[k] == i)
                value += nSubK[k];
        }
        equalizedHistogram[i] = value/MN;
    }
}
