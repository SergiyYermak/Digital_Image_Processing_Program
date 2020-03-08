#  Digital Image Processing Program
## Description
*Application that implements basic concepts and methodologies applicable to digital image processing. Most of the concepts are taken from the forth edition of Digital Image Processing by Rafael C. Gonzalez and Richard E. Woods*

*Here is the exact book* <http://www.imageprocessingplace.com/DIP-4E/dip4e_main_page.htm>

*The concepts that are already included are: Image negatives, log transformations, power-law (gamma) transformations, contrast
streching, intensity-level slicing, bit-plane slicing, 90 degree rotations, image streching, converting color images to gray scale, and
adding a simple "HILL" watermark.*

## Installation/Requirements
*These programs were written on Code Blocks. Specifically, Release 17.12 rev 11256 (2017-12-28 10:44:41) gcc 5.1.0 Windows/unicode - 32 bit\
Note that I used a windows machine, no testing has been done on other machines.\
Additionally, the image files are just lines of numbers, to view these images or any changes that you made using the program, you will need a program that is able to read PPM and PGM files. I used IrfanView Version 4.53 - 64 bit*

*Here is their homepage* <https://www.irfanview.com/>

 ## Usage
 *The book simply describes a digital image as a two dimensional matrix, but does not specify what data structure should be used for
 best results. Therefore, I use my own data structure which is basically a dynamic array within another dynamic array. Furthermore,
 sample inputs are provided for this application. The programs were made to work with PGM and PPM files. So the "sampleinputs" folder
 holds a small variety of images to play with. The images are represented as objects of type Image. Image.h has the constructor and has
 a few helper functions such as readFromFile that help initialize the image. However, to not congest this file, I have seperated most of
 the methods done to it in what I call machines. These files are seperated into catagories, for example, the intensityMachine.h holds
 all functions related to intensity transformations. Therfore, if one would like to preform a intesnsity transformation to a image, one
 must initialize the intensity machine and then call the function they would like with image as the parameter. I provide an example
 bellow of what main.cpp would look like in the case we want a negative image. The main.cpp has a small menu already set up for testing.
 Here is portion of that code.*

     Image m(width, height, brightness, format, fileIn);
     m.readFromFile(fileIn);

     IntensityMachine im;
     Image n(im.negative(m)));

     if(format == "P3")
     {
         n.writeToFile("testColorOutput.ppm");
     }
     else
         n.writeToFile("testGrayOutput.pgm");

 ## Support
 *I don't work at CodeBlocks or IrfanView. So if the problem is with the programs, not my code, then find answers online. However, if 
 you have questions about my code, my email is syerm001@odu.edu*

 ## Roadmap
*Currently, I am splitting up Image.cpp into different machines and adding better comments to each function. However, next on my list
are further chapters in the book that I am using. These chapters are:*
 Next on the list:
 1. Filtering in the Frequency Domain
 2. Image Restoration and Reconstruction
 3. Wavelet and Other Image Transforms
 4. Color Image processing
 5. Image Compression and Watermarking
 6. Morphological Image Processing
