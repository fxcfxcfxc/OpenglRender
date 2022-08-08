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
	Pitch = pitch;
	Yaw = yaw;
	Position = pos;
	WorldUp = worldUp;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm:: cross(Forward, WorldUp));
	Up = glm::normalize(glm:: cross(Forward, Right));

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp);

}



void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}


void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY * 0.001f;
	Yaw -= deltaX * 0.001f;
	UpdateCameraVectors();



}


void Camera::UpdateCameraPos()
{
	Position += Forward * speedZ * 0.02f + Right * speedX * 0.02f + Up * speedY * 0.01f;
}