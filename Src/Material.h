#pragma once

#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class Material
{
public:
	Shader* shader;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess;

	Material(Shader* _Shader, glm::vec3 _Diffuse, glm::vec3 _Specular, glm::vec3 _ambient,float _Shininess);
	
	  

};

