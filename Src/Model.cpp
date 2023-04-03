#include "Model.h"
#include "stb_image.h"

//��ʼ������
Model::Model(std::string path)
{
	modelMatrix = scale( glm:: mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));

	loadModel(path);
}

void Model::ResetTransform()
{
	modelMatrix = scale( glm:: mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
}

//����drawcall ���а�����mesh����
void Model::Draw(Shader* shader)
{
	for (unsigned int i =0; i<meshes.size(); i ++)
	{
		meshes[i].Draw(shader);
	}

}


//���ļ�����ģ�ͣ�����obj�ļ��еĽڵ�
void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	
	//��ȡobj�ļ��еĸ��ڵ�
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |aiProcess_CalcTangentSpace );

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{

		std::cout << "Assimp error" << std::endl;
		return;

	}

	//��ʼ�� ģ������ ���·��
	directory = path.substr(0, path.find_last_of('\\'));
	std::cout << "Success" + directory << std::endl;

	//�����ڵ�
	processNode(scene->mRootNode, scene);
}


//�ݹ����ÿһ���ڵ� ������mesh����
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



//�ӽڵ�����ȡmesh�����ԣ������һ��mesh�෵��
Mesh Model::processMesh(aiMesh* aimesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> TempTextures;

	//���ļ�mesh�� ���㣬���ߣ�uv ������ʱ��������mesh����
	glm::vec3 tempVec;
	for (unsigned int i =0; i <  aimesh->mNumVertices ; i++)
	{
		Vertex tempVertex;
		tempVertex.Position.x = aimesh->mVertices[i].x;
		tempVertex.Position.y = aimesh->mVertices[i].y;
		tempVertex.Position.z = aimesh->mVertices[i].z;

		tempVertex.Normal.x = aimesh->mNormals[i].x;
		tempVertex.Normal.y = aimesh->mNormals[i].y;
		tempVertex.Normal.z = aimesh->mNormals[i].z;

		if (aimesh->mTextureCoords[0])
		{
			tempVertex.TexCoords.x = aimesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = aimesh->mTextureCoords[0][i].y;

		}
		else
		{
			tempVertex.TexCoords = glm::vec2(0, 0);
		}

		tempVertices.push_back(tempVertex);
	}

	for (unsigned int i = 0; i< aimesh->mNumFaces; i++)
	{
		for(unsigned int j =0; j < aimesh->mFaces[i].mNumIndices; j++)
		{
			tempIndices.push_back(aimesh->mFaces[i].mIndices[j]);
		}
	
	}

	 //ͨ��mesh������ �õ� ���ʶ���
	 aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

	 // 1. ��ȡ���ж�Ӧ texture_diffuse�� �����б�
	 std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");

	 // 2. ��ȡ���ж�Ӧ texture_specular �����б�
	 std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

	
	 TempTextures.insert(TempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
	 TempTextures.insert(TempTextures.end(), specularMaps.begin(), specularMaps.end());


	 //����mesh��  mesh ��Ӧ�Ķ��㣬uv����������
	 return Mesh(tempVertices, tempIndices, TempTextures);


}


//
std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{

	// ��ŷ��ص�texture �б�
	std::vector<Texture> textures;
	
	//������ǰ aimesh Я�������в���
	for (unsigned int i=0;i <mat->GetTextureCount(type);i++)
	{
		aiString str;
		//����aiTextureType ���� �õ��������� ����  "glass_dif.png"
		mat->GetTexture(type, i, &str);

		bool skip = false;
		
		//�ж���ͼ�Ƿ��Ѿ�����	������� ֱ�Ӹ��ӵ��б���
		for (unsigned int j =0; j<textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;

			}
		}

		// ������治���ڣ��͹���Texture ���󣬲����뵽textures_loaded �Լ�textures ��
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


void Model::DrawLight(unsigned int &VAO,unsigned int &VBO )
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	//unsigned int VAO,VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glDrawArrays(GL_TRIANGLES,0,36);
	
}

//���������ļ��� ����GPU  ������buffer id
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