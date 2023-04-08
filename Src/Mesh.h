#pragma once

#include <string>
#include <glm.hpp>
#include <vector>
#include "shader.h"
#include <gl/glew.h>

struct Vertex {

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

};
#include "Material.h"

struct Texture{
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh
{
public:
	//field

	std::vector<Vertex> vertices;
	

	std::vector<unsigned int> indices;
	

	std::vector<Texture> textures;


	Mesh(float v[]);
	
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	
	~Mesh();
	

	void Draw(Shader* shader);


private:
	
	unsigned int VAO, VBO, EBO;
	
	void setupMesh();
};

