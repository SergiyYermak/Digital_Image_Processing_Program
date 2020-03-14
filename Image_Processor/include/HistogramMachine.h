#ifndef HISTOGRAMMACHINE_H
#define HISTOGRAMMACHINE_H
#include "Image.h"

class HistogramMachine
{
    public:
        ///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        HistogramMachine() {};

        ///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ~HistogramMachine() {};

        ///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Image histogramEqualizeImage(const Image m);                                                                                                    ///return the histogram equalized image
        Image histogramMatching(const Image input, const Image specified);                                                                              ///return histogram matched image
};

#endif // HISTOGRAMMACHINE_H
