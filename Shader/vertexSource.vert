#version 330 core 
layout(location = 0 ) in vec3 aPos;                    
//layout(location = 1 ) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;


//uniform  ‰»Î
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

// ‰≥ˆ
//out vec4 vertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec4 PosWS;

void main()
{                                            
        gl_Position =  projMat * viewMat * modelMat * vec4(aPos,  1.0); 
        PosWS = modelMat * vec4(aPos,1.0);
        Normal =  mat3(transpose( inverse(modelMat)) ) * aNormal;
        //vertexColor = vec4( aColor, 1.0 );
        TexCoord = aTexCoord;
}