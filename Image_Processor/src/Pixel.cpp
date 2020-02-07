#include "Pixel.h"

///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pixel::Pixel()
{
    red = 0;
    green = 0;
    blue = 0;
    white = 0;
}
Pixel::Pixel(double r, double g, double b)
{
    red = r;
    green = g;
    blue = b;
    white = 0;
}
Pixel::Pixel(double w)
{
    red = 0;
    green = 0;
    blue = 0;
    white = w;
}
///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Pixel::~Pixel(){}
///Setters & Getters---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
///Getters
double Pixel::getPixelRed() const
{
    return red;
}
double Pixel::getPixelGreen() const
{
    return green;
}
double Pixel::getPixelBlue() const
{
    return blue;
}
int Pixel::getPixelWhite() const
{
    return white;
}
///Setters
void Pixel::setPixelRed(const double r)
{
    red = r;
}
void Pixel::setPixelGreen(const double g)
{
    green = g;
}
void Pixel::setPixelBlue(const double b)
{
    blue = b;
}
void Pixel::setPixelWhite(const int w)
{
    white = w;
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
