#include "camera.h"

void Camera::SetCameraPosition(float x, float y, float z)
{
	cameraPos = glm::vec3(x, y, z);
}

void Camera::SetCameraFront(float x, float y, float z)
{
	cameraFront = glm::vec3(x, y, z);
}

void Camera::SetCameraUp(float x, float y, float z)
{
	cameraUp = glm::vec3(x, y, z);
}
