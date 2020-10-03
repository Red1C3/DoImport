#include<DoImport/DoImporter.h>
using namespace DoImport;
int main(){
    DoImporter di;
    int count;
    float* loc=di.readGLTFFile("Assets\\CubeGLTFWBIN.gltf")->getPositionVectors(count,0);
    for(int i=0;i<count;i++){
        cout<<loc[i];
    }
}