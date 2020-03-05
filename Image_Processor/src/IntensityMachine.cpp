#include "IntensityMachine.h"
using namespace std;

///Intensity Transformations-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
* Turns a given image to it's negative form by inverting its intensity values.
*
* @param image          Object of type Image the function will work on
* @return result        Inverted input
*/
Image IntensityMachine::negative(const Image m)
{
    Image result(m);

    int intensity = m.getBrightness();
    if(m.getFormat() == "P3")
    {
        for(int c = 0; c < m.getColumns(); c++)
        {
            for(int r = 0; r < m.getRows(); r++)
            {
                Pixel p = m.getImagePixel(r,c);
                int negativeR = intensity - p.getPixelRed();
                int negativeG = intensity - p.getPixelGreen();
                int negativeB = intensity - p.getPixelBlue();
                p.setPixelRed(negativeR);
                p.setPixelGreen(negativeG);
                p.setPixelBlue(negativeB);
                result.setImagePixel(c,r,p);
            }
        }

    }
    else
    {
        for(int c = 0; c < m.getColumns(); c++)
        {
            for(int r = 0; r < m.getRows(); r++)
            {
                Pixel p = m.getImagePixel(r,c);
                int negative = intensity - p.getPixelWhite();
                p.setPixelWhite(negative);
                result.setImagePixel(c,r,p);
            }
        }
    }
    return result;
}
/**
* Performs a intensity transformation that follows a logarithmic graph
* Formula: New Value = c log(1+r) where c is a constant (c in this method is c = Max Brightness / log(1 + Max Brightness) )
* and r is the pixel's current value.
*
* @param m          Object of type Image the function will work on
* @return result    Image resulted in applying the log transformation
*/
Image IntensityMachine::logTransformation(Image m)
{
    Image result(m);
    if(m.getFormat()=="P3")
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            for(int row = 0; row < m.getRows(); row++)
            {
                Pixel p = m.getImagePixel(row, col);
                int newR = (m.getBrightness()/log(1+m.getBrightness()))*log(1+p.getPixelRed());
                int newG = (m.getBrightness()/log(1+m.getBrightness()))*log(1+p.getPixelGreen());
                int newB = (m.getBrightness()/log(1+m.getBrightness()))*log(1+p.getPixelBlue());
                p.setPixelRed(newR);
                p.setPixelGreen(newG);
                p.setPixelBlue(newB);
                result.setImagePixel(col,row,p);
            }
        }
    }
    else
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            for(int row = 0; row < m.getRows(); row++)
            {
                Pixel p = m.getImagePixel(row, col);
                int newW = (m.getBrightness()/log(1+m.getBrightness()))*log(1+p.getPixelWhite());
                p.setPixelWhite(newW);
                result.setImagePixel(col,row,p);
            }
        }
    }
    return result;
}
/**
* Performs a intensity transformation that follows a power law
* Formula: New Value = c*(r^y) where r is current pixel value divided by max brightness
* y is the gamma provided by the user, and c is the max brightness
* gamma at 1 results in original image, gamma below 1 gives a brighter image and gamma above 1 gives darker image.
*
* @param m          Object of type Image the function will work on
* @return result    Image resulted in applying the log transformation
*/
Image IntensityMachine::powerTransformation(const Image m ,const double gamma)
{
    Image result(m);
    if(m.getFormat()=="P3")
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            for(int row = 0; row < m.getRows(); row++)
            {
                Pixel p = m.getImagePixel(row, col);
                int newR = (pow(((double)p.getPixelRed()/(double)m.getBrightness()),gamma)) * m.getBrightness();
                int newG = (pow(((double)p.getPixelGreen()/(double)m.getBrightness()),gamma)) * m.getBrightness();
                int newB = (pow(((double)p.getPixelBlue()/(double)m.getBrightness()),gamma)) * m.getBrightness();
                p.setPixelRed(newR);
                p.setPixelGreen(newG);
                p.setPixelBlue(newB);
                result.setImagePixel(col, row, p);
            }
        }
    }
    else
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            for(int row = 0; row < m.getRows(); row++)
            {
                Pixel p = m.getImagePixel(row, col);
                int newW = (pow(((double)p.getPixelWhite()/(double)m.getBrightness()),gamma)) * m.getBrightness();
                p.setPixelWhite(newW);
                result.setImagePixel(col, row, p);
            }
        }
    }
    return result;
}
/**
* Performs a contrast stretch on the image
* General formula: Splits the intensity graph into three sections where s = Current Value * slope of section
* The section are (0,0) - (r1, s1), (r1, s1) - (r2, s2), (r2, s2) - (max, max)
*
* @param m                  Object of type image the transformation will be preformed on
* @param r1, s1             The points of the first and second sections
* @param r2, s2             The points of the second and third sections
* @return result            Object of type image returned after the transformation is performed
* @relates calcContrast()   Calculates the s
*/
Image IntensityMachine::contrastStretch(const Image m, const int r1, const int s1, const int r2, const int s2)
{
    Image result(m);
    for(int row = 0; row < m.getRows(); row++)
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            Pixel p = m.getImagePixel(row, col);
            p.setPixelWhite(calcContrast(m.getBrightness(), r1, r2, s1, s2, p.getPixelWhite()));
            result.setImagePixel(col, row, p);
        }
    }
    return result;
}
/**
*
*
*
*/
Image IntensityMachine::intensityLevelSlicing(const Image m, const int a, const int b, const bool showOther)
{
    Image result(m);
    if(showOther == false)
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            for(int row = 0; row < m.getRows(); row++)
            {
                Pixel p = m.getImagePixel(row, col);
                if(p.getPixelWhite() >= a && p.getPixelWhite() <= b) //in range
                {
                    p.setPixelWhite(m.getBrightness()/2);
                    result.setImagePixel(col, row, p);
                }
                else
                {
                    p.setPixelWhite(0);
                    result.setImagePixel(col, row, p);
                }

            }
        }
    }
    else
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            for(int row = 0; row < m.getRows(); row++)
            {
                Pixel p = m.getImagePixel(row, col);
                if(p.getPixelWhite() >= a && p.getPixelWhite() <= b) //in range
                {
                    p.setPixelWhite(m.getBrightness()/1.25);
                    result.setImagePixel(col, row, p);
                }
            }
        }
    }
    return result;
}
Image IntensityMachine::bitPlaneSlice(const Image m, const int bitPlaneNum)
{
    Image bitPlaneImage(m.getColumns(), m.getRows(), 1, "P2", m.getFileName());
    ///for all the pixels
    for(int row = 0; row < m.getRows(); row++)
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            ///grab a pixel
            Pixel p = m.getImagePixel(row, col);
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

Image IntensityMachine::bitPlaneReconstruction(const Image m, int a, int b)
{
    Image reconstructedImage(m.getColumns(), m.getRows(), m.getBrightness(), m.getFormat(), m.getFileName());
    for(int i = a; i >= b; i--)
    {
        addBitPlane(reconstructedImage, bitPlaneSlice(m, i), i);
    }
    return reconstructedImage;
}
void IntensityMachine::addBitPlane(Image reconstructedImage, Image bitPlaneSlice, int bitLevel)
{
    for(int row = 0; row < reconstructedImage.getRows(); row++)
    {
        for(int col = 0; col < reconstructedImage.getColumns(); col++)
        {
            Pixel p = reconstructedImage.getImagePixel(row, col);
            int currentIntensity = p.getPixelWhite();
            int intensity = 0;
            if(bitPlaneSlice.getImagePixel(row, col).getPixelWhite() > 0)
                intensity = pow(2,(bitLevel-1));
            p.setPixelWhite(currentIntensity + intensity);
            reconstructedImage.setImagePixel(col, row, p);
        }
    }
}
int IntensityMachine::calcContrast(const int maxBrightness, const int r1, const int r2, const int s1, const int s2, const double original)
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
        slope = (maxBrightness - s2)/(maxBrightness - r2);
        int value = original - r2;
        output = s2 + (value * slope);
    }
    return output;
}
string IntensityMachine::intToBinary(int input)
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
