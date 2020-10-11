#include<DoImport/pngImporter.h>
using namespace DoImport;
PngImporter::PngImporter(const char* path,bool flipUVs){
    unsigned error=lodepng::decode(data,width,height,path);
    if(error){
        std::cout<<"Couldn't read file "<<path<<std::endl;
        _ASSERT(EXIT_SUCCESS);
    }
    if(flipUVs) PngImporter::flipUVs();
}
void PngImporter::flipUVs(){

}
unsigned char* PngImporter::getData(int& height,int& width){
    height=this->height;
    width=this->width;
    return data.data();
}