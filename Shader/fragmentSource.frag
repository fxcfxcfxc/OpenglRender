#version 330 core                                      
//in vec4 vertexColor;
//in vec2 TexCoord;
in vec4 PosWS;
in vec3 Normal;
out vec4 FragColor;


//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 LightPos;

void main()
{                                    
        //FragColor = vertexColor;
        //FragColor = mix( texture(ourTexture, TexCoord),texture(ourFace, TexCoord) , 0.2) *vec4( ambientColor,1.0);
        vec3 lDir = normalize(LightPos -PosWS.xyz );
        float lambert = max(0,dot(Normal , lDir));


        FragColor = vec4(objColor  * ambientColor  * lambert, 1.0);
        
}
