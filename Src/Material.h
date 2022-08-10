#pragma once

#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class Material
{
public:
	Shader* shader;
	unsigned int diffuse;
	unsigned int specular;
	glm::vec3 ambient;
	float shininess;

	Material(Shader* _Shader, unsigned int _Diffuse, unsigned int _Specular, glm::vec3 _ambient,float _Shininess);
	
	  

};

