#include "Material.h"

Material::Material(Shader* _Shader, unsigned int _Diffuse, unsigned int _Specular, glm::vec3 _ambient, float _Shininess)
	: shader(_Shader), diffuse(_Diffuse), specular(_Specular), ambient(_ambient),shininess(_Shininess)
{

}
