#include "Material.h"

FMaterial::FMaterial(Shader* _Shader, unsigned int _Diffuse, float _Shininess)
	: shader(_Shader), diffuse(_Diffuse),shininess(_Shininess)
{

}
