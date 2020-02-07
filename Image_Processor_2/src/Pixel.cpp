#include "Pixel.h"

///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pixel::Pixel()
{
    red = 0;
    green = 0;
    blue = 0;
    white = 0;

    upLeft = nullptr;
    up = nullptr;
    upRight = nullptr;
    right = nullptr;
    downRight = nullptr;
    down = nullptr;
    downLeft = nullptr;
    left = nullptr;
}
Pixel::Pixel(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
    white = 0;

    upLeft = nullptr;
    up = nullptr;
    upRight = nullptr;
    right = nullptr;
    downRight = nullptr;
    down = nullptr;
    downLeft = nullptr;
    left = nullptr;
}
Pixel::Pixel(int w)
{
    red = 0;
    green = 0;
    blue = 0;
    white = w;

    upLeft = nullptr;
    up = nullptr;
    upRight = nullptr;
    right = nullptr;
    downRight = nullptr;
    down = nullptr;
    downLeft = nullptr;
    left = nullptr;
}
///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pixel::~Pixel(){}
///Setters & Getters---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
///Getters
int Pixel::getPixelRed() const
{
    return red;
}
int Pixel::getPixelGreen() const
{
    return green;
}
int Pixel::getPixelBlue() const
{
    return blue;
}
int Pixel::getPixelWhite() const
{
    return white;
}
///Neighbor Getters
Pixel* Pixel::getUpLeft() const
{
    return upLeft;
}
Pixel* Pixel::getUp() const
{
    return up;
}
Pixel* Pixel::getUpRight() const
{
    return upRight;
}
Pixel* Pixel::getRight() const
{
    return right;
}
Pixel* Pixel::getDownRight() const
{
    return downRight;
}
Pixel* Pixel::getDown() const
{
    return down;
}
Pixel* Pixel::getDownLeft() const
{
    return downLeft;
}
Pixel* Pixel::getLeft() const
{
    return left;
}
///Setters
void Pixel::setPixelRed(const int r)
{
    red = r;
}
void Pixel::setPixelGreen(const int g)
{
    green = g;
}
void Pixel::setPixelBlue(const int b)
{
    blue = b;
}
void Pixel::setPixelWhite(const int w)
{
    white = w;
}
///Neighbor Setters
void Pixel::setUpLeft(Pixel p)
{
    upLeft = &p;
}
void Pixel::setUp(Pixel p)
{
    up = &p;
}
void Pixel::setUpRight(Pixel p)
{
    upRight = &p;
}
void Pixel::setRight(Pixel p)
{
    right = &p;
}
void Pixel::setDownRight(Pixel p)
{
    downRight = &p;
}
void Pixel::setDown(Pixel p)
{
    down = &p;
}
void Pixel::setDownLeft(Pixel p)
{
    downLeft = &p;
}
void Pixel::setLeft(Pixel p)
{
    left = &p;
}
///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Pixel::adjustPixelBrightness(const int factor, const int brightness)
{
    ///red value
    if(red + factor > brightness || red + factor < 0)
    {
        if(red + factor > brightness)
            red = brightness;
        else
            red = 0;
    }
    else
        red = red + factor;
    ///green value
    if(green + factor > brightness || green + factor < 0)
    {
        if(green + factor > brightness)
            green = brightness;
        else
            green = 0;
    }
    else
        green = green + factor;
    ///blue value
    if(blue + factor > brightness || blue + factor < 0)
    {
        if(blue + factor > brightness)
            blue = brightness;
        else
            blue = 0;
    }
    else
        blue = blue + factor;
    ///white value
    if(white + factor > brightness || white + factor < 0)
    {
        if(white + factor > brightness)
            white = brightness;
        else
            white = 0;
    }
    else
        white = white + factor;
}
