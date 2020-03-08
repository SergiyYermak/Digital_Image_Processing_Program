#ifndef INTENSITYMACHINE_H
#define INTENSITYMACHINE_H
#include "Image.h"
#include <string>

class IntensityMachine
{
    public:
        ///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        IntensityMachine() {};

        ///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ~IntensityMachine() {};

        ///Intensity Transformations-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Image adjustBrightness(const Image m, const int factor);                                                                            ///adjust each intensity to be original intensity + factor
        Image negative(const Image m);                                                                                                      ///make a negative of the original image
        Image logTransformation(const Image m);                                                                                             ///perform a log negative transformation on the image
        Image powerTransformation(const Image m, const double gammma);                                                                      ///perform a gamma transformation on the image
        Image contrastStretch(const Image m, const int r1, const int s1, const int r2, const int s2);                                       ///contrast stretch a washed out image
        Image intensityLevelSlicing(const Image m, const int a, const int b, const bool showOther);                                         ///preform intensity slicing from a to b range, true to leave other intensities unchanged
        Image bitPlaneSlice(const Image m, const int bitPlane);                                                                             ///transformation function for generating bit planes
        Image bitPlaneReconstruction(const Image m, const int a, const int b);                                                              ///reconstruct image from bit plane a to b

    private:
        ///Helper Functions
        void addBitPlane(Image reconstructedImage, Image bitPlaneSlice, int bitLevel);                                                      ///helper function for bit plane reconstruction
        int calcContrast(const int maxBrightness, const int r1, const int r2, const int s1, const int s2, const double original);           ///helper function for contrast stretch
        std::string intToBinary(int input);                                                                                                 ///helper function for bit plane slice

};

#endif // INTENSITYMACHINE_H
