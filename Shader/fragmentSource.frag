#version 330 core  

in vec2 TexCoord;
in vec3 posWS;
in vec3 nDirWS;

struct Material{
vec3 ambient;
sampler2D diffuse;
sampler2D specular;
float shininess;
};


struct LightDirection{

float pos;
vec3 color;
vec3 direction;


};

struct LightPoint{

vec3 pos;
vec3 color;
float constant;
float linear;
float quadratic;
};


struct LightSpot{

vec3 pos;
vec3 color;
vec3 direction;
float cosPhyInner;   
float cosPhyOut;

};


uniform LightSpot lightS;
uniform LightPoint lightP;
uniform LightDirection lightd;

uniform Material material;

uniform vec3 ambientColor;
uniform vec3 cameraPos;



out vec4 FragColor;


//平行光
vec3 GetDirectionLight( LightDirection ld, vec3 nDirWS, vec3 vDirWS ,vec3 posWS ,Material mat,vec2 TexCoord)
{
    vec3 directionOut; 
//diffuse
    vec3  lDirWS =  normalize( ld.direction);
    vec3  diffuseTexture = texture(mat.diffuse, TexCoord).rgb;
    vec3 lambert = max(0,  dot( nDirWS,lDirWS) ) * diffuseTexture   * ld.color;


//speuclar
   vec3 rDir =  normalize( reflect(-lDirWS,nDirWS) ); 
   vec3 specularTexture = texture(mat.specular, TexCoord).rgb ;
   vec3 specular = pow( max(dot(rDir, vDirWS),0 ) ,mat.shininess) * ld.color * specularTexture;
    

  directionOut = lambert + specular;
    
  return directionOut;
}


//点光源
vec3 GetPointLight( LightPoint lP, vec3 nDirWS, vec3 vDirWS ,vec3 posWS , Material mat,vec2 TexCoord)
{
    vec3 PointOut;
  
//diffuse
    vec3  lDirWS =  normalize(lP.pos - posWS);
    vec3  diffuseTexture = texture(mat.diffuse, TexCoord).rgb;
    vec3 lambert = max(0,  dot( nDirWS,lDirWS) ) * diffuseTexture  *lP.color; 

//speuclar
   vec3 rDir =  normalize( reflect(-lDirWS,nDirWS) ); 
   vec3 specularTexture = texture(mat.specular, TexCoord).rgb ;
   vec3 specular = pow( max(dot(rDir, vDirWS),0 ) ,mat.shininess) * lP.color * specularTexture;

//attenuation 距离衰减
    float Pointdistance = length(lP.pos - posWS);
    float attenuation  =1.0/ (lP.constant + lP.linear *Pointdistance + lP.quadratic * Pointdistance * Pointdistance);

//merge
    PointOut = (lambert + specular) * attenuation;

  return PointOut;
}

//聚光灯
vec3 GetSpotLight( LightSpot lS, vec3 nDirWS, vec3 vDirWS ,vec3 posWS , Material mat,vec2 TexCoord)
{
    vec3 SpotOut;


//diffuse
    vec3  lDirWS =  normalize(lS.pos - posWS);
    vec3  diffuseTexture = texture(mat.diffuse, TexCoord).rgb;
    vec3 lambert = max(0,  dot( nDirWS,lDirWS) ) * diffuseTexture * lS.color; 

//speuclar
   vec3 rDir =  normalize( reflect(-lDirWS,nDirWS) ); 
   vec3 specularTexture = texture(mat.specular, TexCoord).rgb ;
   vec3 specular = pow( max(dot(rDir, vDirWS),0 ) ,mat.shininess) * lS.color * specularTexture;

//attenuation 距离衰减
    //float Pointdistance = length(LightPos - posWS);
    //float attenuation  =1.0/ (lS.constant + lS.linear *Pointdistance + lS.quadratic * Pointdistance * Pointdistance);

//merge
        // 计算当前角度
        float cosTheta = dot( normalize (posWS - lS.pos), -1 * lDirWS );


        //计算所在角度区域对应的衰减强度
        float spotRatio = 0;
        if(cosTheta > lS.cosPhyInner)
        {               
            
            spotRatio= 1.0f;
        }
        else if(cosTheta >lS.cosPhyOut){

           spotRatio = ( cosTheta -  lS.cosPhyOut) / (lS.cosPhyInner - lS.cosPhyOut );

        }

        else{
            spotRatio= 0.0f;
        }



        SpotOut =  (lambert  + specular ) *spotRatio;

    return SpotOut;
}


void main()
{             
         vec3 diffuseTexture = texture(material.diffuse, TexCoord).rgb;   
         vec3 ambient  =   ambientColor *  diffuseTexture;
         vec3 vDirWs = normalize(cameraPos - posWS);


         vec3 LightMergeColor;

         LightMergeColor += GetDirectionLight(lightd, nDirWS, vDirWs, posWS, material, TexCoord);
         LightMergeColor += GetPointLight(lightP, nDirWS, vDirWs, posWS, material, TexCoord);
         LightMergeColor += GetSpotLight(lightS, nDirWS, vDirWs, posWS, material, TexCoord);
    

         FragColor = vec4( LightMergeColor +ambient , 1.0);
        
}
