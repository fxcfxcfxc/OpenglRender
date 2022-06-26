#include "Shader.h"
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

		printf(vertexSource);
		printf(fragmentSource);


	}

	catch (const std:: exception& ex)
	{
		printf(ex.what());
	}



}





