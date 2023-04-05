#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <glm.hpp>
#include <gl/glew.h>

#include "Shader.h"

class DrawGizmo
{
public:
    static void SetGizmoShader(Shader* GizmoShader,glm::mat4 m, glm::mat4 v, glm::mat4 p);
    static void DrawBox(unsigned int &VAO,unsigned int &VBO);

    static glm::mat4 mMatrix;


private:

};
