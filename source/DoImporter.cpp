#include<DoImport/DoImporter.h>
using namespace DoImport;
GltfImporter* DoImporter::getGLTFImporter(){
    if(gltfImporter==nullptr){
        cout<<"A null gltfImporter was requested"<<endl;
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