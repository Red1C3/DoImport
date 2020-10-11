#pragma once
#include<rapidjson/document.h>
#include<sstream>
#include<fstream>
#include<iostream>
namespace DoImport{
    class GltfImporter{
private:
        struct Attributes{
            float* positionVectors;
            float* normals;
            float* UV_0_Coords;
            int positionVectorsCount;
            int normalsCount;
            int UV_0_CoordsCount;
            ~Attributes(){
                delete[] positionVectors;
                delete[] normals;
                delete[] UV_0_Coords;
            }
        };
        struct Primitvies
        {
            Attributes* attributes;
            unsigned short* indices;
            int indicesCount;
            ~Primitvies(){
                delete attributes;
                delete[] indices;
            }
        };
        struct Mesh{
            const char* name;
            Primitvies * primitives;
            ~Mesh(){
                delete primitives;
            }
        };
        struct Node{
            const char* name;
            Mesh* mesh;
            ~Node(){
                delete mesh;
            }
        };
        struct Scene{
            const char* name;
            Node* nodes;
            int nodesCount;
            ~Scene(){
                delete[] nodes;
            }
        };
        struct Gltf
        {
            Scene* scene;
        };
        std::stringstream sStream;
        Gltf gltf;
        std::string gltfFilePath;
        /*Reads data form an accessor in a GLTF File*/
        char* readDataFromAccessor(int accessor,int& count,const rapidjson::Document& gltfFile);
public:
        /*Constructs the GLTF file existing in the path into RAM*/
        GltfImporter(char* path);
        ~GltfImporter();
        /*Returns a pointer to the first float of position vectors giving the NODE INDEX and changes count varible into floats total count*/
        float* getPositionVectors(unsigned int& count,int nodeIndex);
        /*Returns a pointer to the first float of position vectors giving the NODE NAME and changes count varible into floats total count*/
        float* getPositionVectors(unsigned int& count,const char* nodeName); 
        /*Returns a pointer to the first float of normals vectors giving the NODE INDEX and changes count varible into floats total count*/ 
        float* getNormals(unsigned int& count,int nodeIndex);
        /*Returns a pointer to the first float of normals vectors giving the NODE NAME and changes count varible into floats total count*/
        float* getNormals(unsigned int & count,const char* nodeName);
        /*Returns a pointer to the first float of UV stores in channel 0 vectors giving the NODE INDEX and changes count varible into floats total count*/ 
        float* getUV0Coords(unsigned int& count,int nodeIndex);
        /*Returns a pointer to the first float of UV stores in channel 0 vectors giving the NODE NAME and changes count varible into floats total count*/ 
        float* getUV0Coords(unsigned int& count,const char* nodeName);
        /*Returns a pointer to the first UNSIGNED SHORT of Faces Indices giving the NODE INDEX and changes count varible into UNSIGNED SHORTS total count*/ 
        unsigned short* getFacesIndices(unsigned int& count,int nodeIndex);
        /*Returns a pointer to the first UNSIGNED SHORT of Faces Indices giving the NODE NAME and changes count varible into UNSIGNED SHORTS total count*/ 
        unsigned short* getFacesIndices(unsigned int& count,const char* nodeName);
    };
}