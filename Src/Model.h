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

/**
 * \brief ?????obj??????????model??
 */
class Model
{
public:
	//????
	Model(std::string path);

	//??????????????��???mesh??????????????
	std::vector<Texture> textures_loaded;

	//??????????��?mesh????
	std::vector<Mesh> meshes;

	//obj?????��??????????????
	std::string directory;

	//mesh����
	void Draw(Shader* shader);

	//�ƹ����
	static  void DrawLight(unsigned int &VAO,unsigned int &VBO);
private:
	void loadModel(std:: string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);



};


