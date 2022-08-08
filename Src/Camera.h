#pragma once



#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



class Camera
{
public:
	Camera(glm:: vec3 pos, glm:: vec3 target, glm:: vec3 worldUp);
	Camera(glm::vec3 pos, float pitch, float yaw, glm::vec3 worldUp);
	//~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float speedZ;
	float speedX = 0;
	float speedY = 0;

	glm::mat4 GetViewMatrix();
	void UpdateCameraPos();
	void ProcessMouseMovement(float deltaX, float deltaY);

private:
	void UpdateCameraVectors();

}; 