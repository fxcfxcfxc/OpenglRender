#version 330 core 
layout(location = 0 ) in vec3 aPos;                    
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;



//uniform ����
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//���
//out vec4 vertexColor;
out vec2 TexCoord;
out vec3 nDirWS;
out vec3 posWS;

void main()
{                                             
        gl_Position =  projMat * viewMat * modelMat * vec4(aPos,  1.0); 
        posWS = (modelMat * vec4(aPos,1.0) ) .xyz;
        nDirWS =  mat3(transpose( inverse(modelMat)) ) * aNormal;
        TexCoord = aTexCoord;
}