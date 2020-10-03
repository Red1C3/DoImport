#include<DoImport/gltfImporter.h>
using namespace DoImport;
GltfImporter::GltfImporter(char* path){
    gltfFilePath=string(path);
    {
        int i;
        for(i=gltfFilePath.length()-1;i>=0;i--){
            if(gltfFilePath.at(i)=='\\'){
                break;
            }
        }
        gltfFilePath.erase(i+1);
    }
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
            gltf.scene->nodes[i].mesh->primitives->indices=(unsigned short*)readDataFromAccessor(
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
char* GltfImporter::readDataFromAccessor(int accessor,int& count,const Document& gltfFile){
    count=gltfFile["accessors"][accessor]["count"].GetInt();
    int bufferViewIndex=gltfFile["accessors"][accessor]["bufferView"].GetInt();
    int bufferIndex=gltfFile["bufferViews"][bufferViewIndex]["buffer"].GetInt();
    int byteLength=gltfFile["bufferViews"][bufferViewIndex]["byteLength"].GetInt();
    int byteOffset=gltfFile["bufferViews"][bufferViewIndex]["byteOffset"].GetInt();
    int bufferLength=gltfFile["buffers"][bufferIndex]["byteLength"].GetInt();
    const char* fileName=gltfFile["buffers"][bufferIndex]["uri"].GetString();
    char* data=new char[byteLength];
    fstream fStream(string(gltfFilePath+fileName),ios::in|ios::binary);
    if(fStream.is_open()){
        fStream.seekg(byteOffset,ios::beg);
        fStream.read(data,byteLength);
        fStream.close();
    }else{
        cout<<"Couldn't find file: "<<fileName<<endl;
        assert(EXIT_SUCCESS);
    }
    return data;
}
GltfImporter::~GltfImporter(){
    delete gltf.scene;
}
float* GltfImporter::getPositionVectors(unsigned int& count,int nodeIndex){
    if(nodeIndex>=gltf.scene->nodesCount){
        cout<<"Node parameter is invalid, a null pointer is returned instead"<<endl;
        cout<<"Wrong Index is"<<nodeIndex<<endl;
        count=0;
        return nullptr;
    }
    count=gltf.scene->nodes[nodeIndex].mesh->primitives->attributes->positionVectorsCount;
    return gltf.scene->nodes[nodeIndex].mesh->primitives->attributes->positionVectors;
}
float* GltfImporter::getPositionVectors(unsigned int & count, const char* nodeName){
    string nodeNameModified(nodeName);
    nodeNameModified.append(" ");
    for(int i=0;i<gltf.scene->nodesCount;i++){
        if(strcmp(gltf.scene->nodes[i].name,nodeNameModified.c_str())){
            return getPositionVectors(count,i);
        }
    }
    cout<<"There is no mesh found with the name "<<nodeName<<" , a null pointer is returned instead"<<endl;
    count=0;
    return nullptr;
}
float* GltfImporter::getNormals(unsigned int & count,int nodeIndex){
    if(nodeIndex>=gltf.scene->nodesCount){
        cout<<"Node parameter is invalid,a null pointer is returnd instead"<<endl;
        cout<<"Wrong Index is"<<nodeIndex<<endl;
        count=0;
        return nullptr;
    }
    count=gltf.scene->nodes[nodeIndex].mesh->primitives->attributes->normalsCount;
    return gltf.scene->nodes[nodeIndex].mesh->primitives->attributes->normals;
}
float* GltfImporter::getNormals(unsigned int& count,const char* nodeName){
    string nodeNameModified(nodeName);
    nodeNameModified.append(" ");
    for(int i=0;i<gltf.scene->nodesCount;i++){
        if(strcmp(gltf.scene->nodes[i].name,nodeNameModified.c_str())){
            return getNormals(count,i);
        }
    }
    cout<<"There is no mesh found with the name "<<nodeName<<" , a null pointer is returned instead"<<endl;
    count=0;
    return nullptr;
}
float* GltfImporter::getUV0Coords(unsigned int & count,int nodeIndex){
    if(nodeIndex>=gltf.scene->nodesCount){
        cout<<"Node parameter is invalid,a null pointer is returnd instead"<<endl;
        cout<<"Wrong Index is"<<nodeIndex<<endl;
        count=0;
        return nullptr;
    }
    count=gltf.scene->nodes[nodeIndex].mesh->primitives->attributes->UV_0_CoordsCount;
    return gltf.scene->nodes[nodeIndex].mesh->primitives->attributes->UV_0_Coords;
}
float* GltfImporter::getUV0Coords(unsigned int& count,const char* nodeName){
    string nodeNameModified(nodeName);
    nodeNameModified.append(" ");
    for(int i=0;i<gltf.scene->nodesCount;i++){
        if(strcmp(gltf.scene->nodes[i].name,nodeNameModified.c_str())){
            return getUV0Coords(count,i);
        }
    }
    cout<<"There is no mesh found with the name "<<nodeName<<" , a null pointer is returned instead"<<endl;
    count=0;
    return nullptr;
}
unsigned short * GltfImporter::getFacesIndices(unsigned int& count,int nodeIndex){
    if(nodeIndex>=gltf.scene->nodesCount){
        cout<<"Node parameter is invalid,a null pointer is returnd instead"<<endl;
        cout<<"Wrong Index is"<<nodeIndex<<endl;
        count=0;
        return nullptr;
    }
    count=gltf.scene->nodes[nodeIndex].mesh->primitives->indicesCount;
    return gltf.scene->nodes[nodeIndex].mesh->primitives->indices;
}
unsigned short * GltfImporter::getFacesIndices(unsigned int & count,const char* nodeName){
    string nodeNameModified(nodeName);
    nodeNameModified.append(" ");
    for(int i=0;i<gltf.scene->nodesCount;i++){
        if(strcmp(gltf.scene->nodes[i].name,nodeNameModified.c_str())){
            return getFacesIndices(count,i);
        }
    }
    cout<<"There is no mesh found with the name "<<nodeName<<" , a null pointer is returned instead"<<endl;
    count=0;
    return nullptr;
}