#include "FMesh.h"


FMesh::FMesh(float v[])
{
	this->vertices.resize(36);
	memcpy( &(this->vertices[0] ),v, 36 * 8 * sizeof(float) );
	setupMesh();
}

FMesh::FMesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures) 
{

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}
FMesh::~FMesh() 
{


}

void FMesh::Draw(Shader* shader)
{
	//����mesh�������б�������Ҫʹ�õ��������ݣ����ݸ�shader
	for (unsigned int i =0; i <textures.size(); i++)
	{
		if(textures[i].type =="texture_diffuse")
		{
			//����1 ��
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,textures[i].id);
			shader->SetUniform1i("material.diffuse",0);

		}
		else if (textures[i].type == "texture_specular")
		{
			//����2 ��
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->SetUniform1i("material.specular", 1);

		}

	}


	//��vao
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	//dracall����
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0 );

	//���vao
	glBindVertexArray(0);

	//�������ָ������
	glActiveTexture(GL_TEXTURE0);
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
