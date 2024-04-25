#pragma once
#include "VBO.h"

namespace Engine {
	class VAO {
	public:
		unsigned int ID;
		VAO();

		void LinkVBO(VBO* VBO, float* vertices, size_t size);
		void Bind();
		void Unbind();
		void Delete();
	private:
	};
}
