#include "camera.h"
#include "../time/Time.h"

namespace Engine {
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	{
		cameraPos = position;
		worldUp = up;
		yaw = yaw;
		pitch = pitch;
		UpdateCameraVectors();
	}

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

	void Camera::RotateCamera(float xOffset, float yOffset, bool constrainPitch)
	{
		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		yaw += xOffset;
		pitch += yOffset;

		// Constrain pitch so we cant get upside down
		if (constrainPitch)
		{
			if (pitch > 90.0f)
				pitch = 90.0f;
			if (pitch < -90)
				pitch = 90;
		}

		UpdateCameraVectors();
	}

	void Camera::UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
        // also re-calculate the Right and Up vector
        cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        cameraUp    = glm::normalize(glm::cross(cameraRight, cameraFront));
	}

}