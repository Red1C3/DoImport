#include<DoImport/DoImporter.h>
#pragma comment(lib,"DoImporter.lib")
using namespace DoImport;
using namespace std;
int main(){
    DoImporter di;
    unsigned int count;
    float* pos=di.readGLTFFile("Assets\\CubeGLTFWBIN.gltf")->getPositionVectors(count,0);
    cout<<"Position vectors :"<<endl;
    for(int i=0;i<count;i+=3) cout<<*(pos+i)<<" "<<*(pos+i+1)<<" "<<*(pos+i+2)<<endl;
    float* normals=di.getGLTFImporter()->getNormals(count,0);
    cout<<"Normals :"<<endl;
    for(int i=0;i<count;i+=3) cout<<*(normals+i)<<" "<<*(normals+i+1)<<" "<<*(normals+i+2)<<endl;
    float* UV=di.getGLTFImporter()->getUV0Coords(count,0);
    cout<<"UVs:"<<endl;
    for(int i=0;i<count;i+=2) cout<<*(UV+i)<<" "<<*(UV+i+1)<<endl;
    unsigned short* faces=di.getGLTFImporter()->getFacesIndices(count,"Cube");
    cout<<"Faces indices:"<<endl;
    for(int i=0;i<count;i+=3) cout<<*(faces+i)<<" "<<*(faces+i+1)<<" "<<*(faces+i+2)<<endl;
    di.freeGLTFFile();
}