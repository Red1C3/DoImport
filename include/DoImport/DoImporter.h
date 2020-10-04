#pragma once
#include<DoImport/gltfImporter.h>
namespace DoImport{
    class DoImporter{
private:
        GltfImporter* gltfImporter=nullptr;
public:
        /*Returns a pointer to the GLTF Importer, if there is none,a null pointer is returned*/
        GltfImporter* getGLTFImporter();
        /*Frees up the current GLTF File (if existed), and creates a new GLTF Importer with the file in path*/
        GltfImporter* readGLTFFile(char* path);
        /*Frees up the current GLTF File (if existed), and sets the GLTF Importer pointer to null*/
        void freeGLTFFile();
    };
}