#include "VAO.h"

namespace Engine {
	VAO::VAO()
	{
		glGenVertexArrays(1, &ID);
	}

	void VAO::LinkVBO(VBO* VBO)
	{
		VBO->Bind();
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		VBO->Unbind();
	}

	void VAO::Bind()
	{
		glBindVertexArray(ID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(ID);
	}

	void VAO::Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}
}