#version 330 core                                      
//in vec4 vertexColor;
in vec2 TexCoord;
in vec4 PosWS;
in vec3 Normal;

struct Material{
vec3 ambient;
sampler2D diffuse;
sampler2D specular;
float shininess;
};

uniform Material material;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 LightPos;
uniform vec3 LightColor;
uniform vec3 cameraPos;
uniform vec3 LightDir;


out vec4 FragColor;


void main()
{                                    


        //diffse
        vec3  diffuseTexture = texture(material.diffuse, TexCoord).rgb;
        vec3 lDir = normalize( LightPos - PosWS.xyz );
        //vec3 lDir =LightDir;
        vec3 lambert = max(0,dot(Normal , lDir)) * LightColor * diffuseTexture;
 

        //specualr
        vec3 vDir =  normalize( cameraPos - PosWS.xyz );
        vec3 rDir =  normalize( reflect(-lDir,Normal) ); 
        vec3 specularTexture = texture(material.specular, TexCoord).rgb ;
        vec3 specular = pow( max(dot(rDir, vDir),0 ) ,material.shininess) * LightColor.rgb * specularTexture;


        //ambient
        vec3 ambient  = material.ambient *  ambientColor * diffuseTexture;

        FragColor = vec4( (lambert + ambient + specular)* objColor, 1.0);
        
}
