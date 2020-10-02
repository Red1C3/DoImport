#include<DoImport/gltfImporter.h>
using namespace DoImport;
GltfImporter::GltfImporter(char* path){
    if(!path){cout<<"GLTF Importer was called with a null pointer"; assert(EXIT_SUCCESS);}
    fstream fStream(path,ios::in);
    if(fStream.is_open()) sStream<<fStream.rdbuf();
    fStream.close();
    try
    {
        Document gltfFile;
        gltfFile.Parse(sStream.str().c_str());
        gltf.scene=new Scene();
        gltf.scene->name=gltfFile["scenes"][0]["name"].GetString();
        gltf.scene->nodesCount=gltfFile["scenes"][0]["nodes"].GetArray().Size();
        gltf.scene->nodes=new Node[gltf.scene->nodesCount];
        for(int i=0;i<gltf.scene->nodesCount;i++){
            gltf.scene->nodes[i].name=gltfFile["nodes"][i]["name"].GetString();
            gltf.scene->nodes[i].mesh=new Mesh();
            const int meshIndex=gltfFile["nodes"][i]["mesh"].GetInt();
            gltf.scene->nodes[i].mesh->name=gltfFile["meshes"][meshIndex]["name"].GetString();
            gltf.scene->nodes[i].mesh->primitives=new Primitvies();
            gltf.scene->nodes[i].mesh->primitives->attributes=new Attributes();
            gltf.scene->nodes[i].mesh->primitives->indices=(unsigned int*)readDataFromAccessor(
            gltfFile["meshes"][meshIndex]["primitives"][0]["indices"].GetInt(),
            gltf.scene->nodes[i].mesh->primitives->indicesCount,gltfFile);
            gltf.scene->nodes[i].mesh->primitives->attributes->positionVectors=(float*)readDataFromAccessor(
            gltfFile["meshes"][meshIndex]["primitives"][0]["attributes"]["POSITION"].GetInt(),
            gltf.scene->nodes[i].mesh->primitives->attributes->positionVectorsCount,gltfFile);
            gltf.scene->nodes[i].mesh->primitives->attributes->normals=(float*)readDataFromAccessor(
            gltfFile["meshes"][meshIndex]["primitives"][0]["attributes"]["NORMAL"].GetInt(),
            gltf.scene->nodes[i].mesh->primitives->attributes->normalsCount,gltfFile);
            gltf.scene->nodes[i].mesh->primitives->attributes->UV_0_Coords=(float*)readDataFromAccessor(
            gltfFile["meshes"][meshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"].GetInt(),
            gltf.scene->nodes[i].mesh->primitives->attributes->UV_0_CoordsCount,gltfFile
            );
        }
    }
    catch(const std::exception& e)
    {
        cout<<"Couldn't read file at path "<<path<<endl;
        std::cerr << e.what() << '\n';
        assert(EXIT_SUCCESS);
    }
}