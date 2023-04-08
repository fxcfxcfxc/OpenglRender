#include "FMesh.h"


FMesh::FMesh(float v[])
{
	this->vertices.resize(36);
	memcpy( &(this->vertices[0] ),v, 36 * 8 * sizeof(float) );
	setupMesh();
}

FMesh::FMesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices,FMaterial*  mat) 
{
	this->vertices = vertices;
	this->indices = indices;
	this->material = mat;
	setupMesh();
}

FMesh::~FMesh() 
{


}

void FMesh::Draw()
{
	//绑定渲染着色器
	material->shader->use();
	
	//绑定纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,material->diffuse);
	material->shader->SetUniform1i("material.diffuse",0);
	material->shader->SetUniform1f("material.shininess",material->shininess);

	//绑定vao
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0 );

	//解绑
	glBindVertexArray(0);
}

void FMesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0],GL_STATIC_DRAW);

	//pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);

	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(3 * sizeof(GL_FLOAT)) );

	//uv
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(6 * sizeof(GL_FLOAT)) );

	glBindVertexArray(0);
}
