#include "VBO.h"

namespace Engine {
	VBO::VBO(float* vertices, size_t size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void VBO::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
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