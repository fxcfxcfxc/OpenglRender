#include "Model.h"
#include "stb_image.h"

//初始化数据
Model::Model(std::string path)
{

	loadModel(path);
}

//绘制drawcall 所有包含的mesh对象
void Model::Draw(Shader* shader)
{
	for (unsigned int i =0; i<meshes.size(); i ++)
	{
		meshes[i].Draw(shader);
	}

}


//从文件导入模型，处理obj文件中的节点
void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	
	//获取obj文件中的根节点
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |aiProcess_CalcTangentSpace );

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{

		std::cout << "Assimp error" << std::endl;
		return;

	}

	//初始化 模型纹理 存放路径
	directory = path.substr(0, path.find_last_of('\\'));
	std::cout << "Success" + directory << std::endl;

	//处理节点
	processNode(scene->mRootNode, scene);
}


//递归查找每一个节点 并插入mesh容器
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



//从节点中提取mesh的属性，并组成一个mesh类返回
Mesh Model::processMesh(aiMesh* aimesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> TempTextures;

	//将文件mesh的 顶点，法线，uv 贯入临时，并构建mesh对象
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

	 //通过mesh的索引 拿到 材质对象
	 aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

	 // 1. 读取所有对应 texture_diffuse的 纹理列表
	 std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");

	 // 2. 读取所有对应 texture_specular 纹理列表
	 std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

	
	 TempTextures.insert(TempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
	 TempTextures.insert(TempTextures.end(), specularMaps.begin(), specularMaps.end());


	 //构建mesh类  mesh 对应的顶点，uv，顶点索引
	 return Mesh(tempVertices, tempIndices, TempTextures);


}


//
std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{

	// 存放返回的texture 列表
	std::vector<Texture> textures;
	
	//遍历当前 aimesh 携带的所有材质
	for (unsigned int i=0;i <mat->GetTextureCount(type);i++)
	{
		aiString str;
		//根据aiTextureType 类型 拿到纹理名字 比如  "glass_dif.png"
		mat->GetTexture(type, i, &str);

		bool skip = false;
		
		//判断贴图是否已经存在	，如果是 直接附加到列表中
		for (unsigned int j =0; j<textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;

			}
		}

		// 如果上面不存在，就构建Texture 对象，并插入到textures_loaded 以及textures 中
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