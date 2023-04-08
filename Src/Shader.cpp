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
		

		//???? vertexshader  fragmentshader ????
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment,"FRAGMENT");


		// ???????Program???? ?? attach??  vertex ?? fragment
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");


		//??ú????
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

void Shader::checkCompileErrors(unsigned int ID, std::string type)
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

void Shader::SetRenderingData(glm::mat4 v,glm::mat4 p, glm::vec3 ambientColor,LightDirectional* lightD, LightPoint* lightP,LightSpot* lightS,Camera currentCamera)
{
	

	//glUniformMatrix4fv(glGetUniformLocation(ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(m));
	glUniformMatrix4fv(glGetUniformLocation(ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(v));
	glUniformMatrix4fv(glGetUniformLocation(ID, "projMat"), 1, GL_FALSE, glm::value_ptr(p));


	glUniform3f(glGetUniformLocation(ID, "ambientColor"), ambientColor.x,ambientColor.y, ambientColor.z);
            

	glUniform3f(glGetUniformLocation(ID, "lightd.pos"), lightD->position.x, lightD->position.y, lightD->position.z);
	glUniform3f(glGetUniformLocation(ID, "lightd.direction"), lightD->direction.x, lightD->direction.y, lightD->direction.z);
	glUniform3f(glGetUniformLocation(ID, "lightd.color"), lightD->color.x, lightD->color.y, lightD->color.z);


	glUniform3f(glGetUniformLocation(ID, "lightP.pos"), lightP->position.x, lightP->position.y, lightP->position.z );
	glUniform3f(glGetUniformLocation(ID, "lightP.color"), lightP->color.x, lightP->color.y, lightP->color.z);
	glUniform1f(glGetUniformLocation(ID, "lightP.constant"), lightP->constant);
	glUniform1f(glGetUniformLocation(ID, "lightP.linear"), lightP->linear);
	glUniform1f(glGetUniformLocation(ID, "lightP.quadratic"), lightP->quadratic);



	glUniform3f(glGetUniformLocation(ID, "lightS.pos"), lightS->position.x, lightS->position.y, lightS->position.z );
	glUniform3f(glGetUniformLocation(ID, "lightS.color"), lightS->color.x, lightS->color.y, lightS->color.z );
	glUniform3f(glGetUniformLocation(ID, "lightS.direction"), lightS->direction.x, lightS->direction.y, lightS->direction.z );
	glUniform1f(glGetUniformLocation(ID, "lightS.cosPhyInner"), lightS->cosPhyInner );
	glUniform1f(glGetUniformLocation(ID, "lightS.cosPhyOut"), lightS->cosPhyOut );

	glUniform3f( glGetUniformLocation(ID,"cameraPos"), currentCamera.Position.x, currentCamera.Position.y, currentCamera.Position.z);

	SetUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	//SetUniform1f("material.shininess",64.0f);
	
}

void Shader::SetRenderingData(glm::mat4 m, glm::mat4 v,glm::mat4 p)
{
		

	glUniformMatrix4fv(glGetUniformLocation(ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(m));
	glUniformMatrix4fv(glGetUniformLocation(ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(v));
	glUniformMatrix4fv(glGetUniformLocation(ID, "projMat"), 1, GL_FALSE, glm::value_ptr(p));

}

void Shader::SetModelTransform(glm::mat4 m )
{
	glUniformMatrix4fv(glGetUniformLocation(ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(m));
}