#include "Mesh.h"


Mesh::Mesh(float v[])
{
	this->vertices.resize(36);
	memcpy( &(this->vertices[0] ),v, 36 * 8 * sizeof(float) );
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) 
{

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}
Mesh::~Mesh() 
{


}

void Mesh::Draw(Shader* shader)
{
	//遍历mesh的纹理
	for (unsigned int i =0; i <textures.size(); i++)
	{
		if(textures[i].type =="texture_diffuse")
		{
			//纹理1 绑定
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,textures[i].id);
			shader->SetUniform1i("material.diffuse",0);

		}
		else if (textures[i].type == "texture_specular")
		{
			//纹理2 绑定
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->SetUniform1i("material.specular", 1);

		}

	}


	//绑定vao
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	//dracall绘制
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0 );

	//解绑vao
	glBindVertexArray(0);

	//纹理指向充值
	glActiveTexture(GL_TEXTURE0);
}


void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0],GL_STATIC_DRAW);

	//pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)) );

	//uv
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)) );

	glBindVertexArray(0);
}
