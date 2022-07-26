#include "Camera.h"


Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp)
{
	Position = pos;
	WorldUp = worldUp;
	Forward = glm:: normalize(target - pos);
	Right =glm:: normalize( glm::cross(Forward, WorldUp) );
	Up = glm::normalize(glm:: cross(Forward, Right));
 
}


Camera::Camera(glm:: vec3 pos, float pitch, float yaw, glm:: vec3 worldUp)
{
	Position = pos;
	WorldUp = worldUp;
	Forward.x = glm::cos(pitch) * glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);
	Right = glm::normalize(glm:: cross(Forward, worldUp));
	Up = glm::normalize(glm:: cross(Forward, Right));

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp);

}