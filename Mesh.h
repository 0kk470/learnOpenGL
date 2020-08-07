#pragma once
#include "glheader.h"
#include <assimp/types.h>

using std::vector;
using std::string;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture
{
	GLuint id;
	std::string type;
	aiString Path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

	~Mesh();

	void Draw(Shader& shader);

private:

	GLuint VBO, VAO, EBO;

	void SetUpMesh();
};

