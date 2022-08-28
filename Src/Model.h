#pragma once


#include <vector>
#include <string>
#include <iostream>


#include "Mesh.h"
#include "shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model
{
public:
	Model(std::string path);
	std::vector<Texture> textures_loaded;

	//meshÈÝÆ÷
	std::vector<Mesh> meshes;
	std::string directory;
	void Draw(Shader* shader);
private:
	void loadModel(std:: string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};





