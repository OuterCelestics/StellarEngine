#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

namespace Engine {
	class Shaders {
	public:
		GLuint ID;
		Shaders(const GLchar* vertexPath, const GLchar* fragmentPath);
		void Activate();
		void Delete();
	private:
		std::string get_file_contents(const char* filename);
	private:
		unsigned int vertex, fragment;
	};
}

#endif // !BUFFER_CLASS_H
 