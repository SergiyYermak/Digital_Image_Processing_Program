#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
    public:
        ///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Pixel();                                                                                ///default constructor that initialized the private members
        Pixel(int r, int g, int b);                                                             ///constructor for colored pixel, initializes red, green, and blue to the passed values, and initializes white to 0
        Pixel(int w);                                                                           ///constructor for white pixel, initializes white to the passed values, and 0 to all the other

        ///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        virtual ~Pixel();

        ///Setters & Getters---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ///Getters
        int getPixelRed() const;                                                                ///returns hue of red
        int getPixelGreen() const;                                                              ///returns hue of green
        int getPixelBlue() const;                                                               ///return hue of blue
        int getPixelWhite() const;                                                              ///return hue of white
        ///Neighbor Getters
        Pixel* getUpLeft() const;                                                               ///return the pointer of the upleft neighbor
        Pixel* getUp() const;                                                                   ///return the pointer of the up neighbor
        Pixel* getUpRight() const;                                                              ///return the pointer of the upright neighbor
        Pixel* getRight() const;                                                                ///return the pointer of the right neighbor
        Pixel* getDownRight() const;                                                            ///return the pointer of the downright neighbor
        Pixel* getDown() const;                                                                 ///return the pointer of the down neighbor
        Pixel* getDownLeft() const;                                                             ///return the pointer of the downleft neighbor
        Pixel* getLeft() const;                                                                 ///return the pointer of the left neighbor
        ///Setters
        void setPixelRed(const int r);                                                          ///sets hue of red to "r"
        void setPixelGreen(const int g);                                                        ///sets hue of green to "g"
        void setPixelBlue(const int b);                                                         ///sets hue of blue to "b"
        void setPixelWhite(const int w);                                                        ///sets hue of white to "w"
        ///Neighbor Setters
        void setUpLeft(Pixel p);                                                                ///gives a pixel address to the upleft pointer
        void setUp(Pixel p);                                                                    ///gives a pixel address to the up pointer
        void setUpRight(Pixel p);                                                               ///gives a pixel address to the upright pointer
        void setRight(Pixel p);                                                                 ///gives a pixel address to the right pointer
        void setDownRight(Pixel p);                                                             ///gives a pixel address to the downright pointer
        void setDown(Pixel p);                                                                  ///gives a pixel address to the down pointer
        void setDownLeft(Pixel p);                                                              ///gives a pixel address to the downleft pointer
        void setLeft(Pixel p);                                                                  ///gives a pixel address to the left pointer

        ///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        void adjustPixelBrightness(const int factor, const int brightness);                     ///adjusts the hue of all the values by a factor, must be passed the max brightness as to not over adjust

    private:
        int red;                                                                                ///hue of red
        int green;                                                                              ///hue of green
        int blue;                                                                               ///hue of blue
        int white;                                                                              ///hue of white
        ///Pixel's neighbors
        Pixel* upLeft;
        Pixel* up;
        Pixel* upRight;
        Pixel* right;
        Pixel* downRight;
        Pixel* down;
        Pixel* downLeft;
        Pixel* left;

};
#endif // PIXEL_H
