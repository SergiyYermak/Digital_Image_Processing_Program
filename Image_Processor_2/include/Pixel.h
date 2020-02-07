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
        Pixel* getUpLeft() const;
        Pixel* getUp() const;
        Pixel* getUpRight() const;
        Pixel* getRight() const;
        Pixel* getDownRight() const;
        Pixel* getDown() const;
        Pixel* getDownLeft() const;
        Pixel* getLeft() const;
        ///Setters
        void setPixelRed(const int r);                                                          ///sets hue of red to "r"
        void setPixelGreen(const int g);                                                        ///sets hue of green to "g"
        void setPixelBlue(const int b);                                                         ///sets hue of blue to "b"
        void setPixelWhite(const int w);                                                        ///sets hue of white to "w"
        ///Neighbor Setters
        void setUpLeft(Pixel p);
        void setUp(Pixel p);
        void setUpRight(Pixel p);
        void setRight(Pixel p);
        void setDownRight(Pixel p);
        void setDown(Pixel p);
        void setDownLeft(Pixel p);
        void setLeft(Pixel p);

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
