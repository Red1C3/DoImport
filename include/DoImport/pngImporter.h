#pragma once
#include<lodepng/lodepng.h>
#include<iostream>
#include<vector>
namespace DoImport{
    class PngImporter{
private:
        /* Holds image data in RGBARGBA...*/
        std::vector<unsigned char> data;
        unsigned height,width;
public:
        /*Constructs the PNG file provided into RAM, enable flipVertically in case you are importing a texture into an OpenGL-Powered engine*/
        PngImporter(const char* path,bool flipVertically=false);
        /*Flips the image vertically, helpful if you are importing your texture into an OpenGL-Powered engine*/
        void flipVertically();
        /*return a vector to the image data in format RGBARGBA, while also setting height and width into image's*/
        std::vector<unsigned char> getData(unsigned int& height,unsigned int& width);
    };
}