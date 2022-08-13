#pragma once


#include <glm.hpp>
#include <gtx/rotate_vector.hpp>
class LightSpot
{
public:
	LightSpot(glm::vec3 _poition, glm::vec3 _angle, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	void UpdateDirection();

	glm::vec3 position;
	glm::vec3 angle;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;

	float cosPhyInner = 0.9f;
	float cosPhyOut = 0.85f;

};

