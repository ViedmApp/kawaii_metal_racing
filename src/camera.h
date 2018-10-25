#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera
{
private:
	float yaw = -90.;
	float pitch = 0.0f;
	float field_of_view = 45.;
	float speed;
	float sensitivity;
	float zoom;

	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

public:
	camera(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUp, float field_of_View, float pitch, float yaw);
	~camera();

	//setters
	void setFOV(float fov);
	void setPitch(float pitch);

	//getters
	float getFOV();
	float getPitch();

private:
	void updateCameraVectors();
};