#  Digital Image Processing Program
## Description
*Application that implements basic concepts and methodologies applicable to digital image processing. Most of the concepts are taken from the forth edition of Digital Image Processing by Rafael C. Gonzalez and Richard E. Woods*

*Here is the exact book* <http://www.imageprocessingplace.com/DIP-4E/dip4e_main_page.htm>

*However, most is not everything. The book simply describes a digital image as a two dimensional matrix, but does not specify what data structure should be used for best results. Therefore, there are two sets of image processors within this project. One that uses a dynamic array within a dynamic array (Image_Processor) and another that uses a two dimensional linked list (Image_Processor_2). However, Image_Processor is far more developed, and is the main application. Furthermore, sample inputs are provided for this application. The programs were made to work with PGM and PPM files. So the "sampleinputs" folder holds a small variety of images to play with.*

## Installation/Requirements
*These programs were written on Code Blocks. Specifically, Release 17.12 rev 11256 (2017-12-28 10:44:41) gcc 5.1.0 Windows/unicode - 32 bit\
Note that I used a windows machine, no testing has been done on other machines.\
Additionally, the image files are just lines of numbers, to view these images or any changes that you made using the program, you will need a program that is able to read PPM and PGM files. I used IrfanView Version 4.53 - 64 bit*

*Here is their homepage* <https://www.irfanview.com/>

 ## Usage
 *The images are represented as objects of type Image. Therefore, most of the manipulation functions are in Image.h. Image.h is heavily commented, so just read what each function does. Furthermore, main.cpp has a small menu already set up for testing.
 Here is portion of that code.*


      Image m(width, height, brightness, format, fileIn);
      m.readFromFile(fileIn);

      /// INSERT TEST CODE

      /// ****************

      m.writeToFile("testOutput.pgm");

*Simply insert m.functionName below INSERT TEST CODE and run it, then you can see the results using the IrfanView. Change testOutput.pgm to testOutput.ppm if you want to test a colored image.*

 ## Support
 *I don't work at CodeBlocks or IrfanView. So if the problem is with the programs, not my code, then find answers online. However, if you have questions about my code, my email is syerm001@odu.edu*

 ## Roadmap
 *Image_Processor_2 was made to fix a specific design issue. However, during development, the issue I was trying to resolve came back. I plan to complete the bare minimum structure for Image_Processor_2, but most of the image processing is going to be implemented in Image_Processor.*


 Next on the list:
 1. Filtering in the Frequency Domain
 2. Image Restoration and Reconstruction
 3. Wavelet and Other Image Transforms
 4. Color Image processing
 5. Image Compression and Watermarking
 6. Morphological Image Processing
