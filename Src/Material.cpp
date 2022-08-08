#include "Material.h"

Material::Material(Shader* _Shader, glm::vec3 _Diffuse, glm::vec3 _Specular, glm::vec3 _ambient, float _Shininess)
	: shader(_Shader), diffuse(_Diffuse), specular(_Specular), ambient(_ambient),shininess(_Shininess)
{

}
