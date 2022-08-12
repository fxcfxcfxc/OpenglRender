#include  "LightSpot.h"



LightSpot::LightSpot(glm::vec3 _pos, glm::vec3 _angle, glm::vec3 _Color)
	: position(_pos), angle(_angle), color(_Color)
{
	
	UpdateDirection();
}



void LightSpot::UpdateDirection()
{

	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angle.z);
	direction = glm::rotateX(direction, angle.x);
	direction = glm::rotateY(direction, angle.y);
	direction = -direction;


}
