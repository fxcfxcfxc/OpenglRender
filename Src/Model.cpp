#include "Model.h"
#include "stb_image.h"

//��ʼ������
Model::Model(std::string path)
{

	loadModel(path);
}

//��������mesh
void Model::Draw(Shader* shader)
{
	for (unsigned int i =0; i<meshes.size(); i ++)
	{
		meshes[i].Draw(shader);
	}

}


//���ļ�����ģ��
void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	//�õ�scene �ڵ�
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |aiProcess_CalcTangentSpace );

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{

		std::cout << "Assimp error" << std::endl;
		return;

	}

	//��ʼ�� ģ������ ���·��
	directory = path.substr(0, path.find_last_of('\\'));
	std::cout << "Success" + directory << std::endl;

	processNode(scene->mRootNode, scene);
}


//�ݹ���ҽڵ� ������mesh����
void Model::processNode(aiNode* node, const  aiScene* scene)
{
	//------------------------�ݹ�ִ������-------------------------------------//
	std::cout << node->mName.data << std::endl;

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];

		//���ļ��� ����mesh����
		meshes.push_back(processMesh(curMesh, scene));
	}
	//-------------------------------------------------------------//


	//�ݹ�
	for (unsigned int i =0;  i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
		
	}

}



//���mesh ���ļ��е�����
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> TempTextures;

	//���ļ�mesh�� ���㣬���ߣ�uv ������ʱ��������mesh����
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


	//����mesh�� ������
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






//��������ļ��� ����GPU  ������buffer id
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