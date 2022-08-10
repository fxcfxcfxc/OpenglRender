#include "Shader.h"
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std:: ifstream vertexFile;
	std:: ifstream fragmentFile;
	
	std:: stringstream vertexSStream;
	std:: stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions( std:: ifstream:: failbit || std:: ifstream:: badbit);
	vertexFile.exceptions( std:: ifstream:: failbit || std:: ifstream::	badbit); 

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std:: exception("open file error");
		}

		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();


		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//printf(vertexSource);
		//printf(fragmentSource);
		

		//创建 vertexshader  fragmentshader 对象
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment,"FRAGMENT");


		// 创建一个Program对象， 并 attach上  vertex 和 fragment
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");


		//使用后删除
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	catch (const std:: exception& ex)
	{
		printf(ex.what());
	}



}


void Shader::use()
{
	glUseProgram(ID);

}

void Shader::SetUniform3f(const char* Name, glm::vec3 Param)
{
	glUniform3f(glGetUniformLocation(ID, Name),Param.x, Param.y, Param.z );

}


void Shader::SetUniform1f(const char* Name, float Param)
{
	glUniform1f(glGetUniformLocation(ID, Name),Param );
}

void Shader::SetUniform1i(const char* Name, int slot)
{
	glUniform1i(glGetUniformLocation(ID,Name),slot);

}


void  Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int  success;
	char infoLog[512];

	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "shader compile error: " << infoLog << std::endl;
		}
		


	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std:: cout << "program compile error: " << infoLog << std:: endl;
		}
	}

}