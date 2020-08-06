#pragma once
#include "glheader.h"

using std::vector;
using std::string;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	std::string type;
};


const char* DIFFUSE_TEX_NAME = "texture_diffuse";
const char* SPECULAR_TEX_NAME = "texture_specular";

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

