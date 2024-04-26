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
	class ENGINE_API Camera
	{
	public:
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	public:
		void SetCameraPosition(float x, float y, float z);
		void SetCameraFront(float x, float y, float z);
		void SetCameraUp(float x, float y, float z);

		void MoveCamera(Camera_Movement direction, float speed);

	private:
	};

}