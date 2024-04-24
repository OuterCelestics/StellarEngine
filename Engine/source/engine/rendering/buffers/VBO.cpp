#include "VBO.h"
#include <glad/glad.h>

namespace Engine {
	VBO::VBO()
	{
		glGenBuffers(1, &ID);
	}

	void VBO::Bind(float* vertices, size_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);
	}

	void VBO::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VBO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}