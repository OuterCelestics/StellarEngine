#include "camera.h"
#include "../time/Time.h"

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

void Camera::MoveCamera(Camera_Movement direction, float speed)
{
	float velocity = speed * Time::deltaTime;
	switch (direction)
	{
	case FORWARD:
		cameraPos += cameraFront * speed;
		break;
	case BACKWARD:
		cameraPos += cameraFront * speed;
		break;
	case LEFT:
		cameraPos -+ cameraUp
		break;
	case RIGHT:
		break;
	case UP:
		break;
	case DOWN:
		break;
	default:
		break;
	}
}
