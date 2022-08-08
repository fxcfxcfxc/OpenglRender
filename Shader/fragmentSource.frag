#version 330 core                                      
//in vec4 vertexColor;
//in vec2 TexCoord;
in vec4 PosWS;
in vec3 Normal;
out vec4 FragColor;


struct Material{
vec3 ambient;
vec3 diffuse;
vec3 specular;

float shininess;
};



uniform Material material;

//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 LightPos;
uniform vec3 LightColor;
uniform vec3 cameraPos;


void main()
{                                    
        //FragColor = vertexColor;
        //FragColor = mix( texture(ourTexture, TexCoord),texture(ourFace, TexCoord) , 0.2) *vec4( ambientColor,1.0);

        //diffse
        vec3 lDir = normalize(LightPos -PosWS.xyz );
        vec3 lambert = max(0,dot(Normal , lDir)) * LightColor;
 

        //specualr
        vec3 vDir =  normalize( cameraPos - PosWS.xyz );
        vec3 rDir =  normalize( reflect(-lDir,Normal) ); 
        vec3 specular = pow( max(dot(rDir, vDir),0 ) ,material.shininess) * LightColor.rgb * material.specular;


        //ambient
        vec3 ambient  = material.ambient *  ambientColor;
        FragColor = vec4( (lambert + ambientColor + specular) * objColor, 1.0);
        
}
