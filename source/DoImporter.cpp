#include<DoImport/DoImporter.h>
using namespace DoImport;
GltfImporter* DoImporter::getGLTFImporter(){
    if(gltfImporter==nullptr){
        std::cout<<"A null gltfImporter was requested"<<std::endl;
        assert(EXIT_SUCCESS);
    }
    return gltfImporter;
}
GltfImporter* DoImporter::readGLTFFile(char* path){
    freeGLTFFile();
    gltfImporter=new GltfImporter(path);
    return gltfImporter;
}
void DoImporter::freeGLTFFile(){
    delete gltfImporter;
    gltfImporter=nullptr;
}
PngImporter* DoImporter::getPNGImporter(){
    if(pngImporter==nullptr){
        std::cout<<"A null PNGImporter was requested"<<std::endl;
        assert(EXIT_SUCCESS);
    }
    return pngImporter;
}
PngImporter* DoImporter::readPNGFile(const char* path,bool flipUVs){
    freePNGFile();
    pngImporter=new PngImporter(path,flipUVs);
    return pngImporter;
}
void DoImporter::freePNGFile(){
    delete pngImporter;
    pngImporter=nullptr;
}