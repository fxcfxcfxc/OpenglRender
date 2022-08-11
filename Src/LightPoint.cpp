#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _pos, glm::vec3 _angle, glm::vec3 _Color)
	: position(_pos), angle(_angle), color(_Color)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;

}
