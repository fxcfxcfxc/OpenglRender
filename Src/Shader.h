#pragma once
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Shader
{

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std:: string vertexString;
	std:: string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;

	void use();
	void SetUniform3f(const char* Name, glm::vec3 param);
	void SetUniform1f(const char* Name, float Param);

private:

	//ºÏ≤‚±‡“Î
	void checkCompileErrors(unsigned int ID,std:: string type);
};

