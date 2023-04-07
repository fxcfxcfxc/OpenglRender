#pragma once

#include <string>
#include <glm.hpp>
#include <vector>
#include "shader.h"
#include <gl/glew.h>


#include "Material.h"

struct MeshVertex {

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

};

struct MeshTexture{
	unsigned int id;
	std::string type;
	std::string path;
};


/**
 * \brief һ��mesh ���� �������ݣ���������������
 */
class FMesh
{
public:
	//field
	//�����б�
	std::vector<MeshVertex> vertices;
	
	//���������б�
	std::vector<unsigned int> indices;
	
	//�����б�
	std::vector<MeshTexture> textures;

	//function
	FMesh(float v[]);
	
	FMesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
	
	~FMesh();
	
	//����drawcall����
	void Draw(Shader* shader);


private:
	
	unsigned int VAO, VBO, EBO;
	
	void setupMesh();
};

