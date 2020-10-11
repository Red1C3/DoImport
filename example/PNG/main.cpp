#include<iostream>
#include<DoImport/DoImporter.h>
#include<lodepng/lodepng.h>
#pragma comment(lib,"DoImporter.lib")
using namespace DoImport;
using namespace std;
int main(){
    DoImporter di;
    di.readPNGFile("Assets/texture.png",true);
    unsigned int height,width;
    vector<unsigned char> data=di.getPNGImporter()->getData(height,width);
    vector<unsigned char> databin;
    lodepng::encode(databin,data,width,height);
    lodepng::save_file(databin,"Assets/flipped.png");
}