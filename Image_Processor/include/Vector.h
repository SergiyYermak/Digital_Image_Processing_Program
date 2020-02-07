#ifndef VECTOR_H
#define VECTOR_H
#include "Pixel.h"

class Vector
{
    public:
        ///Constructors-------------------------------------------------------------------------------------------------
        Vector();                                                                   ///Default constructor
        Vector(const int n);                                                        ///n dimensional constructor, make a dynamic array of size n

        ///De-constructor-----------------------------------------------------------------------------------------------
        ~Vector();

        ///Getter & Setters---------------------------------------------------------------------------------------------
        ///Getters
        int getDimensions() const;                                                  ///return size of the array
        Pixel getVectorPixel(const int pos) const;                                  ///returns Pixel object at position "pos"
        ///Setters
        void setVectorPixel(const int pos, Pixel p);                                ///sets Pixel p in the dynamic array at position "pos"
        ///Functions----------------------------------------------------------------------------------------------------
        Vector reverseVector();                                                     ///returns a reversed version of the dynamic array (used in the 180 rotation under Image.cpp)

    private:
        int dimensions;                                                             ///size of the dynamic array
        Pixel *pixels;                                                              ///dynamic array of Pixels

};
#endif // VECTOR_H
