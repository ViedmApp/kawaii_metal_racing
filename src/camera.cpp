#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



camera::camera(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUp, float field_of_view, float pitch, float yaw)
{
	this->cameraPosition = cameraPosition;
	this->cameraFront = cameraFront;
	this->cameraUp = cameraUp;
	this->field_of_view = field_of_view;
	updateCameraVectors();
}


camera::~camera()
{
}

void camera::setFOV(float fov)
{
	this->field_of_view = fov;
}

void camera::setPitch(float pitch)
{
	this->pitch = pitch;
}

float camera::getFOV()
{
	return field_of_view;
}

float camera::getPitch()
{
	return pitch;
}

void camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	//cameraRight = glm::normalize(glm::cross(front, up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//cameraUp = glm::normalize(glm::cross(Right, Front));
}