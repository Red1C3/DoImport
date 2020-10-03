#pragma once
#include<DoImport/gltfImporter.h>
namespace DoImport{
    class DoImporter{
private:
        GltfImporter* gltfImporter=nullptr;
public:
        GltfImporter* getGLTFImporter();
        GltfImporter* readGLTFFile(char* path);
        void freeGLTFFile();
    };
}