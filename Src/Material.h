#pragma once

#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class FMaterial
{
public:
	Shader* shader;
	unsigned int diffuse;
	float shininess;
	FMaterial();
	FMaterial(Shader* _Shader, unsigned int _Diffuse, float _Shininess);
	


};

