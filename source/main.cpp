#include<DoImport/DoImporter.h>
using namespace DoImport;
int main(){
    DoImporter di;
    unsigned int count;
    unsigned short* loc=di.readGLTFFile("Assets\\CubeGLTFWBIN.gltf")->getFacesIndices(count,"Cube");
    for(int i=0;i<count;i++){
        cout<<loc[i]<<endl;
    }
    loc=di.readGLTFFile("Assets\\CubeGLTFWBIN.gltf")->getFacesIndices(count,"Cube");
    for(int i=0;i<count;i++){
        cout<<loc[i]<<endl;
    }
}