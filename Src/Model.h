#pragma once


#include <vector>
#include <string>
#include <iostream>

#include "Mesh.h"
#include "shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);


class Model
{
public:
	//field
	std::vector<Texture> textures_loaded;

	std::vector<Mesh> meshes;

	std::string directory;
	
	glm::mat4  modelMatrix;

	//function
	Model(std::string path);
	
	void Draw(Shader* shader);

	void ResetTransform();
	
private:
	void loadModel(std:: string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};


