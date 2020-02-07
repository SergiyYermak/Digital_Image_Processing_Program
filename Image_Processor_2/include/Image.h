#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include "Pixel.h"

class Image
{
    public:
        ///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Image();
        Image(const int columns, const int rows, const int brightness, const std::string formt, const std::string fName);

        ///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        virtual ~Image();

        ///Getter & Setters----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ///Getters
        int getColumns() const;
        int getRows() const;
        int getBrightness() const;
        std::string getFormat() const;
        std::string getFileName() const;

        ///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        void addPixel(Pixel p);
        void readFromFile(const std::string fileIn);
        //void drawToConsole();

    private:
        Pixel *head;
        Pixel *currentPix;
        Pixel *currentFirstCol;

        int maxColumns;
        int maxRows;
        int currentCol;
        int currentRow;
        int maxBrightness;
        std::string format;
        std::string fileName;
};

#endif // IMAGE_H
