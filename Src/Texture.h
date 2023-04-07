#pragma once
#include <iostream>
#include <direct.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class FTexture
{
private:
    //field
    int height;
    int width;
    int channel;
public:
    //field
    unsigned int Id;
    //function
    FTexture(std::string filename);
    
};
