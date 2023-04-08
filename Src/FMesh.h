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

/**
 * \brief 一个mesh 包含 顶点数据，顶点索引，纹理
 */
class FMesh
{
public:
	//field

	std::vector<MeshVertex> vertices;
	

	std::vector<unsigned int> indices;

	//材质
	FMaterial* material;
	
	//function
	FMesh(float v[]);
	
	FMesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices,FMaterial*  mat);
	
	~FMesh();
	

	void Draw();


private:
	
	unsigned int VAO, VBO, EBO;
	
	void setupMesh();
};

