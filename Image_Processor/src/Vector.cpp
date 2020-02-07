#include "Vector.h"
#include <iostream>
using namespace std;
///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vector::Vector()                                                                    ///The default constructor just initializes an empty 3 element dynamic array
{
    pixels = new Pixel[3];
    dimensions = 3;
    pixels[0] = Pixel();
    pixels[1] = Pixel();
    pixels[2] = Pixel();
}
Vector::Vector(const int n)
{
    dimensions = n;
    pixels = new Pixel[n];
    for(int i = 0; i < n; i++)
        pixels[i] = Pixel();
}
///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vector::~Vector(){}
///Setters & Getters---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
///Getters
int Vector::getDimensions() const
{
    return dimensions;
}
///get any coordinate
Pixel Vector::getVectorPixel(const int pos) const
{
    if(pos >= getDimensions() || pos < 0)
        cout << "ERROR: Can not return pixel at position " << pos << " as it does not exists";
    return pixels[pos];
}
///Setters
void Vector::setVectorPixel(const int pos, Pixel p)
{
    if(pos >= getDimensions())
        cout << "ERROR: Position " << pos << " does not exist." << endl;
    pixels[pos] = p;
}
///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Vector Vector::reverseVector()
{
    Vector v(getDimensions());
    for(int i = 0; i < getDimensions(); i++)
    {
        Pixel p = getVectorPixel(getDimensions()-1-i);
        v.setVectorPixel(i,p);
    }
    return v;
}
