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
	
	std:: string vertexString;
	std:: string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;

	
	//构造
	Shader(const char* vertexPath, const char* fragmentPath);
	
	//绑定当前opengl使用的shader id
	void use();

	//传递shader参数
	void SetUniform3f(const char* Name, glm::vec3 param);
	void SetUniform1f(const char* Name, float Param);
	void SetUniform1i(const char* Name, int slot);

	//为shader设置所需的渲染参数
	void SetRenderingData(glm::mat4 m, glm::mat4 v,glm::mat4 p, glm::vec3 ambientColor,LightDirectional* lightD, LightPoint* lightP,LightSpot* lightS,Camera currentCamera) ;
	// 可以用来设置灯光辅助显示的数据
	void SetRenderingData(glm::mat4 m, glm::mat4 v,glm::mat4 p, Camera currentCamera) ;

	enum Slot
	{
		Diffuse,
		Specular
	};

private:

	//检测编译
	void checkCompileErrors(unsigned int ID,std:: string type);
};

