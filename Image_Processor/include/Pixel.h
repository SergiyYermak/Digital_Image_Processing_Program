#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
    public:
        ///Constructors--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Pixel();                                                                            ///default constructor that initialized the private members
        Pixel(double r, double g, double b);                                                ///constructor for colored pixel, initializes red, green, and blue to the passed values, and initializes white to 0
        Pixel(double w);                                                                    ///constructor for white pixel, initializes white to the passed values, and 0 to all the other

        ///De-constructors-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        virtual ~Pixel();

        ///Setters & Getters---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ///Getters
        double getPixelRed() const;                                                         ///returns hue of red
        double getPixelGreen() const;                                                       ///returns hue of green
        double getPixelBlue() const;                                                        ///return hue of blue
        int getPixelWhite() const;                                                          ///return hue of white
        ///Setters
        void setPixelRed(const double r);                                                   ///sets hue of red to "r"
        void setPixelGreen(const double g);                                                 ///sets hue of green to "g"
        void setPixelBlue(const double b);                                                  ///sets hue of blue to "b"
        void setPixelWhite(const int w);                                                    ///sets hue of white to "w"
        ///Functions-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        void adjustPixelBrightness(const int factor, const int brightness);                 ///adjusts the hue of all the values by a factor, must be passed the max brightness as to not over adjust

    private:
        double red;                                                                         ///hue of red
        double green;                                                                       ///hue of green
        double blue;                                                                        ///hue of blue
        double white;                                                                       ///hue of white
};
#endif // PIXEL_H
