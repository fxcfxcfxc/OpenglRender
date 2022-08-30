#include "Model.h"
#include "stb_image.h"

//初始化数据
Model::Model(std::string path)
{

	loadModel(path);
}

//绘制所有mesh
void Model::Draw(Shader* shader)
{
	for (unsigned int i =0; i<meshes.size(); i ++)
	{
		meshes[i].Draw(shader);
	}

}


//从文件导入模型
void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	//拿到scene 节点
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |aiProcess_CalcTangentSpace );

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{

		std::cout << "Assimp error" << std::endl;
		return;

	}

	//初始化 模型纹理 存放路径
	directory = path.substr(0, path.find_last_of('\\'));
	std::cout << "Success" + directory << std::endl;

	processNode(scene->mRootNode, scene);
}


//递归查找节点 并插入mesh容器
void Model::processNode(aiNode* node, const  aiScene* scene)
{
	//------------------------递归执行内容-------------------------------------//
	std::cout << node->mName.data << std::endl;

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];

		//从文件中 插入mesh容器
		meshes.push_back(processMesh(curMesh, scene));
	}
	//-------------------------------------------------------------//


	//递归
	for (unsigned int i =0;  i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
		
	}

}



//组成mesh 从文件中的数据
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> TempTextures;

	//将文件mesh的 顶点，法线，uv 贯入临时，并构建mesh对象
	glm::vec3 tempVec;
	for (unsigned int i =0; i <  mesh->mNumVertices ; i++)
	{
		Vertex tempVertex;
		tempVertex.Position.x = mesh->mVertices[i].x;
		tempVertex.Position.y = mesh->mVertices[i].y;
		tempVertex.Position.z = mesh->mVertices[i].z;

		tempVertex.Normal.x = mesh->mNormals[i].x;
		tempVertex.Normal.y = mesh->mNormals[i].y;
		tempVertex.Normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;

		}
		else
		{
			tempVertex.TexCoords = glm::vec2(0, 0);
		}

		tempVertices.push_back(tempVertex);
	}

	for (unsigned int i = 0; i< mesh->mNumFaces; i++)
	{
		for(unsigned int j =0; j < mesh->mFaces[i].mNumIndices; j++)
		{
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	
	}


	 aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	 // 1. diffuse maps
	 std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	 TempTextures.insert(TempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
	 // 2. specular maps
	 std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	 TempTextures.insert(TempTextures.end(), specularMaps.begin(), specularMaps.end());


	//构建mesh类 并返回
	 return Mesh(tempVertices, tempIndices, TempTextures);


}


//
std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{

	std::vector<Texture> textures;
	for (unsigned int i=0;i <mat->GetTextureCount(type);i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;
		//-----
		for (unsigned int j =0; j<textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;

			}
		}
		//-----
		if (!skip)
		{
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}

	}
		
	return textures;
}






//将纹理从文件中 导出GPU  并返回buffer id
unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}