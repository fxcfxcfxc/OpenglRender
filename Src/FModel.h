#pragma once


#include <vector>
#include <string>
#include <iostream>
#include "shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "FMesh.h"


class FModel
{
public:
	//-----------------------------------field
	
	std::vector<FMesh> meshes;

	std::string directory;

	glm::mat4  modelMatrix;

	FMaterial* material;
	
	//---------------------------------function
	
	FModel(std::string path,FMaterial* mat);

	void Draw();

	void UpdateTransform(float angle,glm::vec3 position);

	void AddMaterial(FMaterial* mat);
	
private:
	//-----------------------------------field

	
	//---------------------------------function
	void loadModel(std:: string path);
	

	void processNode(aiNode* node, const aiScene* scene);

	FMesh processMesh(aiMesh* mesh, const aiScene* scene);

};


