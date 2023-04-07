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
 * \brief 一个mesh 包含 顶点数据，顶点索引，纹理
 */
class FMesh
{
public:
	//field
	//顶点列表
	std::vector<MeshVertex> vertices;
	
	//顶点索引列表
	std::vector<unsigned int> indices;
	
	//纹理列表
	std::vector<MeshTexture> textures;

	//function
	FMesh(float v[]);
	
	FMesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
	
	~FMesh();
	
	//调用drawcall绘制
	void Draw(Shader* shader);


private:
	
	unsigned int VAO, VBO, EBO;
	
	void setupMesh();
};

