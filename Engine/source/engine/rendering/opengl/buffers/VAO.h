#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
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

#endif // !BUFFER_CLASS_H
