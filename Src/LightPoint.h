#pragma once

#include <glm.hpp>
#include <gtx/rotate_vector.hpp>
class LightPoint
{
public:
	LightPoint(glm::vec3 _pos, glm::vec3 _angle, glm::vec3 _Color = glm::vec3(1.0f, 1.0f, 1.0f ));
	~LightPoint();
	glm::vec3 position;
	glm::vec3 angle;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;
	

};

