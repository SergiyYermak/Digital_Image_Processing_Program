#ifndef IMAGE_H
#define IMAGE_H
#include "Vector.h"
#include <string>
class Image : Vector
{
    public:
        ///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Image();                                                                                                                            ///default constructor, creates 3 by 3 empty matrix with 255 brightness empty format and empty fileName
        Image(const int columns, const int rows, const int brightness, const std::string form, const std::string fName);                    ///main constructor, created columns by rows matrix and initializes private members to the passed values

        ///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ~Image();

        ///Getter & Setters----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ///Getters
        int getColumns() const;                                                                                                             ///returns the size of image array
        int getRows() const;                                                                                                                ///returns the size of pixel array
        int getBrightness() const;                                                                                                          ///returns the value for max brightness
        std::string getFormat() const;                                                                                                      ///returns the format of the image
        std::string getFileName() const;                                                                                                    ///returns the file name associated with the image
        Pixel getImagePixel(const int row, const int column);                                                                               ///returns the Pixel p at position (row,column)
        Vector getRowVector(const int row);                                                                                                 ///builds and returns Vector v at matrix row position "row"
        Vector getColumnVector(const int column);                                                                                           ///returns Vector from image array at position "column"
        ///Setters
        void setImagePixel(const int column, const int row, Pixel input);                                                                   ///sets Pixel input at position (row, column)
        void setRowVector(const int row, Vector &v);                                                                                        ///sets Vector v(dynamic array v) at matrix row position "row"
        void setColumnVector(const int column, Vector &v);                                                                                  ///sets Vector v(dynamic array v) at matrix array position "column"
        ///Operators-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        void operator= (Image obj);
        ///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        void writeToFile();                                                                                                                 ///writes the Image data to a file associated with it
        void writeToFile(std::string fileIn);                                                                                               ///writes the Image to a new file name
        void readFromFile(const std::string fileIn);                                                                                        ///builds Pixels and populates the matrix with the data from the give fileIn file
        Image rotateImage(const int choice);                                                                                                ///rotates image based on 3 choices (1. 90 clockwise, 2. 90 counter clockwise, 3. 180 upside down)
        void adjustBrightness(const int factor);                                                                                            ///add(subtract if negative) factor to the pixels hue values
        void addWatermark(const int brightness, const int letterWidth, const int letterHeight, const int firstRow, const int firstCol);     ///add "HILL" watermark to the image, the watermark has a black to white hue, letter width, letter height, and starting location
        Image stretchImage(const int widthFactor, const int heightFactor);                                                                  ///stretch image by an integer factor
        void convertToGray();                                                                                                               ///converts colored image to gray scale
        //void drawToConsole();                                                                                                             ///Used if running a windows machine for comfort. To use, uncomment this line, line 1, 2, and 443 - 481 in Image.cpp
        ///Intensity Transformations-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        void negative();                                                                                                                    ///make a negative of the original image
        void logTransformation();                                                                                                           ///perform a log negative transformation on the image
        void powerTransformation(const double gammma);                                                                                      ///perform a gamma transformation on the image
        void contrastStretch(const int r1, const int s1, const int r2, const int s2);                                                       ///contrast stretch a washed out image
        void intensityLevelSlicing(const int a, const int b, const bool showOther);                                                         ///preform intensity slicing from a to b range, true to leave other intensities unchanged
        Image bitPlaneSlice(const int bitPlane);                                                                                            ///transformation function for generating bit planes
        Image bitPlaneReconstruction(const int a, const int b);                                                                             ///reconstruct image from bit plane a to b
        ///Histogram Processing------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        void makeEqualizedHistogram();
        ///TODO: Histogram Matching
        ///TODO: Local Histogram Processing



    private:
        ///Variables
        Vector *image;
        double *equalizedHistogram;
        int numColumns;
        int numRows;
        int maxBrightness;
        std::string format;
        std::string fileName;
        ///Functions
        int calcContrast(const int r1, const int r2, const int s1, const int s2, const double original);                                    ///helper function for contrast stretch
        std::string intToBinary(int input);                                                                                                 ///helper function for bit plane slice
        void addBitPlane(Image bitPlaneSlice, int bitLevel);                                                                                ///helper function for bit plane reconstruction
};
#endif // IMAGE_H
