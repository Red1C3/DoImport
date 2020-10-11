#pragma once
#include<DoImport/gltfImporter.h>
#include<DoImport/pngImporter.h>
namespace DoImport{
    class DoImporter{
private:
        GltfImporter* gltfImporter=nullptr;
        PngImporter* pngImporter=nullptr;
public:
        /*Returns a pointer to the GLTF Importer, if there is none,a null pointer is returned*/
        GltfImporter* getGLTFImporter();
        /*Frees up the current GLTF File (if existed), and creates a new GLTF Importer with the file in path*/
        GltfImporter* readGLTFFile(char* path);
        /*Frees up the current GLTF File (if existed), and sets the GLTF Importer pointer to null*/
        void freeGLTFFile();
        /*Returns a pointer to the PNG Importer, if there is none,a null pointer is returned*/
        PngImporter* getPNGImporter();
        /*Frees up the current PNG File (if existed), and creates a new PNG Importer with the file in path,enable flip vertically if you are using an OpenGL-Powered engine*/
        PngImporter* readPNGFile(const char* path,bool flipUVs=false);
        /*Frees up the current PNG File (if existed), and sets the PNG Importer pointer to null*/
        void freePNGFile();
    };
}