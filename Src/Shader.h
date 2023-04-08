#pragma once
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Camera.h"


class Shader
{

public:
	//field
	std:: string vertexString;
	std:: string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;
	
	enum Slot
	{
		Diffuse,
		Specular
	};


	//function
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void SetUniform3f(const char* Name, glm::vec3 param);
	void SetUniform1f(const char* Name, float Param);
	void SetUniform1i(const char* Name, int slot);

	void SetRenderingData(glm::mat4 v,glm::mat4 p, glm::vec3 ambientColor,LightDirectional* lightD, LightPoint* lightP,LightSpot* lightS,Camera currentCamera) ;

	void SetRenderingData(glm::mat4 m, glm::mat4 v,glm::mat4 p) ;

	void SetModelTransform(glm::mat4 m );


private:


	void checkCompileErrors(unsigned int ID,std:: string type);
};

