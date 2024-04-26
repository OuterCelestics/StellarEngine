#pragma once
#include <glm.hpp>
#include "../../core.h"

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

namespace Engine {
	// Default camera values
	const float YAW         = -90.0f;
	const float PITCH       =  0.0f;
	const float SPEED       =  2.5f;
	const float SENSITIVITY =  0.1f;
	const float ZOOM        =  45.0f;

	class ENGINE_API Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		// Camera Attributes
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 worldUp;
		
		// Euler Angles
		float yaw;
		float pitch;

		// CameraOptions
		float movementSpeed;
		float mouseSensitivity = 1;
		float zoom;

	public:
		void SetCameraPosition(float x, float y, float z);
		void SetCameraFront(float x, float y, float z);
		void SetCameraUp(float x, float y, float z);

		void MoveCamera(Camera_Movement direction, float speed);
		void RotateCamera(float xOffset, float yOffset, bool constrainPitch);
	private:
		void UpdateCameraVectors();
	};

}