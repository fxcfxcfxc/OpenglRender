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


struct Texture{
	unsigned int id;
	std::string type;
	std::string path;
};


/**
 * \brief һ��mesh ���� �������ݣ���������������
 */
class Mesh
{
public:
	//�����б�
	std::vector<Vertex> vertices;
	
	//���������б�
	std::vector<unsigned int> indices;
	
	//�����б�
	std::vector<Texture> textures;

	
	Mesh(float v[]);
	
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	
	~Mesh();
	
	//����drawcall����
	void Draw(Shader* shader);


private:
	
	unsigned int VAO, VBO, EBO;
	
	void setupMesh();
};

