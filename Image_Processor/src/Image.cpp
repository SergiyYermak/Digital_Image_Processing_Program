//#define _WIN32_WINNT 0x500
//#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
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
Image::Image(const Image &obj)
{
    image = new Vector[obj.getColumns()];
    for (int i = 0; i < obj.getColumns(); i++)
    {
        Vector v(obj.getRows());
        image[i] = v;
    }
    numColumns = obj.getColumns();
    numRows = obj.getRows();
    maxBrightness = obj.getBrightness();
    format = obj.getFormat();
    fileName = obj.getFileName();
    for(int row = 0; row < obj.getRows(); row++)
    {
        for(int col = 0; col < obj.getColumns(); col++)
        {
            Pixel p = obj.getImagePixel(row, col);
            setImagePixel(col, row, p);
        }
    }
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
Pixel Image::getImagePixel(const int row, const int column) const
{
    Vector v = image[column];
    return v.getVectorPixel(row);
}
Vector Image::getRowVector(const int row) const
{
    Vector v(getColumns());
    for(int i = 0; i < getColumns(); i++)
    {
        Pixel p = getImagePixel(row,i);
        v.setVectorPixel(i,p);
    }
    return v;
}
Vector Image::getColumnVector(const int column) const
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
    numColumns = obj.getColumns();
    numRows = obj.getRows();
    maxBrightness = obj.getBrightness();
    format = obj.getFormat();
    fileName = obj.getFileName();
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
