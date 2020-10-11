#include<DoImport/pngImporter.h>
using namespace DoImport;
using namespace std;
PngImporter::PngImporter(const char* path,bool flipVertically){
    unsigned error=lodepng::decode(data,width,height,path);
    if(error){
        std::cout<<"Couldn't read file "<<path<<std::endl;
        _ASSERT(EXIT_SUCCESS);
    }
    if(flipVertically) PngImporter::flipVertically();
}
void PngImporter::flipVertically(){
    vector<unsigned char> correctedVector;
    for(int i=height-1;i>=0;i--){
        for(int j=0;j<width*4;j++){
            correctedVector.push_back(data[i*width*4+j]);
        }
    }
    data=correctedVector;
}
std::vector<unsigned char> PngImporter::getData(unsigned int& height,unsigned int& width){
    height=this->height;
    width=this->width;
    return data;
}