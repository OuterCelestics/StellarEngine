#pragma once

namespace Engine {
	class VBO 
	{
	public:
		unsigned int  ID;
		VBO();
		void Bind(float* vertices, size_t size);
		void Unbind();
		void Delete();

	private:
	};
}
