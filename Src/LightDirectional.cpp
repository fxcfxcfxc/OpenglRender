#include "LightDirectional.h"


LightDirectional::LightDirectional(glm::vec3 _pos, glm::vec3 _angle, glm::vec3 _color )
	: position(_pos), angle(_angle), color(_color)
{

	UpdateDirectional();
}


void LightDirectional:: UpdateDirectional()
{
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angle.z);
	direction = glm::rotateX(direction, angle.x);
	direction = glm::rotateY(direction, angle.y);
	direction = -direction;

}