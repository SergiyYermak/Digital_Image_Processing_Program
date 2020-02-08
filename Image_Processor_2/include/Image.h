#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include "Pixel.h"

class Image
{
    public:
        ///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Image();                                                                                                                ///default constructor
        Image(const int columns, const int rows, const int brightness, const std::string formt, const std::string fName);       ///image constructor

        ///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        virtual ~Image();

        ///Getter & Setters----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ///Getters
        int getColumns() const;                                                                                                 ///return the actual number of columns, width of image
        int getRows() const;                                                                                                    ///return the actual number of rows, height of image
        int getBrightness() const;                                                                                              ///return the max brightness of pixels
        std::string getFormat() const;                                                                                          ///return the format of the image
        std::string getFileName() const;                                                                                        ///return the file name

        ///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        void addPixel(Pixel p);
        void readFromFile(const std::string fileIn);
        void drawToConsole();

    private:
        Pixel *ImageArr;
        Pixel *head;
        Pixel *currentPix;
        Pixel *currentFirstCol;

        int currentNumOfPixels;
        int maxColumns;
        int maxRows;
        int currentCol;
        int currentRow;
        int maxBrightness;
        std::string format;
        std::string fileName;
};

#endif // IMAGE_H
