#include "HistogramMachine.h"

///Helper Functions Declarations---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int * makeUnnormalizedHistogram(const Image m);                                                                                                  ///function that returns unnormalizedHistogram array of image m
double * makeNormalizedHistogram(const int maxIntensity, const int rows, const int columns, const int *unnormalized);                            ///function that returns normalizedHistogram array of image m

///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
* Returns a histogram equalized image
* General Formula: Gij = floor((maxIntesity) * summation(from n = 0 to Fij of PsubN))
* Gij is pixel intensity at pixel (i,j) = (row, col) and maxIntensity is images' max brightness
* Fij is the intensity of pixel at (i,j) and PsubN is normalized Histogram value at index n
*
*
* @param m                              image which will be equalized
* @relates makeUnnormalizedHistogram    used to create unnormalized histogram that is needed for both normalized and equalized histograms
* @relates makeNormalizedHistogram      used to create normalized histogram that is needed for equalized histogram
*/
Image HistogramMachine::histogramEqualizeImage(const Image m)
{
    int * unnormalizedHistogram = makeUnnormalizedHistogram(m);
    double * normalizedHistogram = makeNormalizedHistogram(m.getBrightness(), m.getRows(), m.getColumns(), unnormalizedHistogram);

    Image result(m);
    for(int row = 0; row < m.getRows(); row++)
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            int Fij = m.getImagePixel(row, col).getPixelWhite();
            double PsubN = 0.0;
            for(int n = 0; n <= Fij; n++)
            {
                PsubN += normalizedHistogram[n];
            }
            int newIntensity = floor(m.getBrightness() * PsubN);
            Pixel p;
            p.setPixelWhite(newIntensity);
            result.setImagePixel(col, row, p);
        }
    }
    return result;
}
/**
* Transformation of an image so that its histogram matches a specified histogram.
*
* 1.Compute the histogram, Pr(r), of the input image, and use it in Eq. (3-20) to map
*   the intensities in the input image to the intensities in the histogram-equalized
*   image. Round the resulting values, Sk, to the integer range [0, L-1]
* 2.Compute all values if function G(Zq) using the Eq.(3-21) for q = 0,1,2,...,L-1,
*   where Pz(Zi) are the values of the specified histogram. Round the values of G to
*   integers in the range [0,L-1]. Store the rounded values of G in a lookup table.
* 3.For every value of Sk, k = 0,1,2,...,L-1, use the stored values of G from Step 2
*   to find the corresponding value of Zq so that G(Zq) is closest to Sk. Store these
*   mappings from s to z. When more than one value of Zq gives the same match
*   (i.e., the mapping is not unique), choose the smallest value by convention.
* 4.Form the histogram-specified image by mapping every equalized pixel with value
*   Sk to the corresponding pixel with value Zq in the histogram-specified image,
*   using the mapping found in Step 3
*/
Image HistogramMachine::histogramMatching(const Image input, const Image specified)
{
    //Step 1
    int * specifiedUnnormalizedHistogram = makeUnnormalizedHistogram(specified);
    double * specifiedHistogram = makeNormalizedHistogram(specified.getBrightness(), specified.getRows(), specified.getColumns(), specifiedUnnormalizedHistogram);

    int * unnormalizedHistogram = makeUnnormalizedHistogram(input);
    double * Pr = makeNormalizedHistogram(input.getBrightness(), input.getRows(), input.getColumns(), unnormalizedHistogram);

    int maxIntensity = input.getBrightness();
    int S[maxIntensity]= {0};
    for(int k = 0; k < maxIntensity; k++)
    {
        double value = 0;
        for(int j = 0; j <= k; j++)
        {
            value += Pr[j];
        }
        S[k] = round(maxIntensity * value);
    }

    //Step 2
    int Gz[maxIntensity];
    for(int q = 0; q < maxIntensity; q++)
    {
        double value = 0;
        for(int i = 0; i <= q; i++)
        {
            value += specifiedHistogram[i];
        }
        Gz[q] = round(maxIntensity * value);
    }

    //Step 3
    int mapping[maxIntensity];
    for(int k = 0; k < maxIntensity; k++)
    {
        int index = 0;
        int diff = abs(S[k] - Gz[0]);
        for(int q = 0; q < maxIntensity; q++)
        {
            int newDiff = abs(S[k] - Gz[q]);
            if(newDiff <= diff)
            {
                diff = newDiff;
                index = q;
            }
        }
        mapping[k] = index;
    }

    //Step 4
    Image histogramSpecified(input);
    int rows = histogramSpecified.getRows();
    int columns = histogramSpecified.getColumns();
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < columns; col++)
        {
            int inputPixelValue = histogramSpecified.getImagePixel(row, col).getPixelWhite();
            int newValue = inputPixelValue;
            for(int i = 0; i < maxIntensity; i++)
            {
                if(S[i] == inputPixelValue)
                    newValue = mapping[i];
            }
            Pixel p(newValue);
            histogramSpecified.setImagePixel(col, row, p);
        }
    }
    return histogramSpecified;
}
///Helper Functions Implementations-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
* Makes an array representing the unnormalized histogram
*
* General formula: H(RsubK) = NsubK where RsubK denotes intensities and NsubK is the number of pixels with intensity RsubK
* Unnormalized Histogram is an array in which the indices are the intensity levels ranging from [0 - maxIntensity]
* and the values inside those indices are the number of pixels that have intensity at that index.
*
* @param m                                     image whose values will be used for the histogram
*/
int * makeUnnormalizedHistogram(const Image m)
{
    int * unnormalizedHistogram = new int[m.getBrightness()] { 0 };
    for(int row = 0; row < m.getRows(); row++)
    {
        for(int col = 0; col < m.getColumns(); col++)
        {
            int pixelIntensity = m.getImagePixel(row, col).getPixelWhite();
            unnormalizedHistogram[pixelIntensity] += 1;
        }
    }
    return unnormalizedHistogram;
}
/**
* Makes an array representing the normalized histogram
*
* General formula: P(RsubK) = H(RsubK)/MN = NsubK/MN where NsubK is the number of pixels with intensity k
* and MN is image rows times columns
* Normalized Histogram is an array in which the indices are the intensity levels ranging from [0 - maxIntensity]
* and the values inside are the probability of that intensity in the image.
*
* @param maxIntensity                           used as the array size and loop limit
* @param rows                                   used with columns to find MN
* @param columns                                used with rows to find MN
* @param unnormalized                           array which is the H(RsubK) in the formula
*/
double * makeNormalizedHistogram(const int maxIntensity, const int rows, const int columns, const int *unnormalized)
{
    double * normalizedHistogram = new double[maxIntensity] { 0.0 };
    int MN = rows * columns;
    for(int i = 0; i < maxIntensity; i++)
    {
        normalizedHistogram[i] = (double)unnormalized[i]/(double)MN;
    }
    return normalizedHistogram;
}
