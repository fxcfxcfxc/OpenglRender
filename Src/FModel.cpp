#include "FModel.h"
#include "stb_image.h"


FModel::FModel(std::string path, FMaterial* mat)
{
	modelMatrix = glm::scale( glm:: mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	this->material = mat;
	loadModel(path);
}

void FModel::AddMaterial(FMaterial* mat)
{
	this->material = mat;
}

void FModel::UpdateTransform(float angle,glm::vec3 position)
{
	modelMatrix = scale( glm:: mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::translate(modelMatrix, position);
}

void FModel::Draw()
{
	material->shader->SetModelTransform(modelMatrix);
	for (unsigned int i =0; i<meshes.size(); i ++)
	{
		if(material ==nullptr)
		{
			break;
		}
		meshes[i].material = material;
		meshes[i].Draw();
	}

}

void FModel::loadModel(std::string path)
{
	Assimp::Importer importer;
	

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |aiProcess_CalcTangentSpace );

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{

		std::cout << "Assimp error" << std::endl;
		return;

	}


	directory = path.substr(0, path.find_last_of('\\'));
	std::cout << "Success" + directory << std::endl;


	processNode(scene->mRootNode, scene);
}

void FModel::processNode(aiNode* node, const  aiScene* scene)
{
	
	std::cout << node->mName.data << std::endl;

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];

		
		meshes.push_back(processMesh(curMesh, scene));
	}
	



	for (unsigned int i =0;  i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
		
	}

}

FMesh FModel::processMesh(aiMesh* aimesh, const aiScene* scene)
{
	std::vector<MeshVertex> tempVertices;
	std::vector<unsigned int> tempIndices;

	for (unsigned int i =0; i <  aimesh->mNumVertices ; i++)
	{
		MeshVertex tempVertex;
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

	 return FMesh(tempVertices, tempIndices, material);


}



