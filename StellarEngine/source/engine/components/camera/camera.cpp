#include "camera.h"
#include "../time/Time.h"

namespace Engine {
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
		float velocity = speed * Engine::Time::deltaTime;
		switch (direction)
		{
		case FORWARD:
			cameraPos += cameraFront * speed;
			break;
		case BACKWARD:
			cameraPos -= cameraFront * speed;
			break;
		case LEFT:
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp))* (speed * Engine::Time::deltaTime);
			break;
		case RIGHT:
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (speed * Engine::Time::deltaTime);
			break;
		case UP:
			cameraPos += cameraUp * speed;
			break;
		case DOWN:
			cameraPos += -cameraUp * speed;
			break;
		default:
			break;
		}
	}

}