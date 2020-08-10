#pragma once

#include "glheader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<map>

using std::vector;
using std::string;
using std::map;

class Model
{
public:
    /*  函数   */
    Model(const char* path)
    {
        LoadModel(path);
    }
    void Draw(Shader& shader);
private:
    /*  模型数据  */
    vector<Mesh> meshes;
    string directory;
    map<string, Texture> textures_loaded;

    void LoadModel(string path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName, const aiScene* scene);
};

