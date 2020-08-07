#include "Model.h"

void Model::Draw(Shader& shader)
{
	for (auto mesh : meshes)
	{
		mesh.Draw(shader);
	}
}

void Model::LoadModel(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (auto i = 0; i < node->mNumMeshes; ++i)
	{
		auto mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (auto i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	//Position
	for (auto i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		glm::vec3 vec(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.Position = vec;

		vec.x = mesh->mNormals[i].x;
		vec.y = mesh->mNormals[i].y;
		vec.z = mesh->mNormals[i].z;
		vertex.Normal = vec;

		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertex.TexCoords = glm::vec2(0);
		}

		vertices.push_back(vertex);
	}

	//Indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//Material
	if (mesh->mMaterialIndex >= 0)
	{
		auto material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = LoadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = LoadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;

	for (auto i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString name;
		mat->GetTexture(type, i, &name);
		auto toFind = textures_loaded.find(name.C_Str());
		if (toFind != textures_loaded.end())
		{
			textures.push_back(toFind->second);
		}
		else
		{
			Texture tex;
			auto filePath = StringUtil::Format("%s/%s", directory.c_str(), name.C_Str());
			tex.id = Resource::LoadTexture(filePath.c_str(), GL_REPEAT, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
			tex.type = typeName;
			tex.Path = name;
			textures.push_back(tex);
			textures_loaded[name.C_Str()] = tex;
		}
	}

	return textures;
}
