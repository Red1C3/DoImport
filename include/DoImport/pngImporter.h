#pragma once
#include<lodepng/lodepng.h>
#include<iostream>
#include<vector>
namespace DoImport{
    class PngImporter{
private:
        std::vector<unsigned char> data;
        unsigned height,width;
public:
        PngImporter(const char* path,bool flipUVs=false);
        void flipUVs();
        unsigned char* getData(int& height,int& width);
    };
}