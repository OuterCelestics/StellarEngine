#include "shaderClass.h"

namespace Engine {
	Shaders::Shaders(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		std::string vertexCode = get_file_contents(vertexPath);
		std::string fragmentCode = get_file_contents(fragmentPath);

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);

		glLinkProgram(ID);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shaders::Activate()
	{
		glUseProgram(ID);
	}

	void Shaders::Delete()
	{
		glDeleteProgram(ID);
	}

	std::string Shaders::get_file_contents(const char* filename)
	{
		std::ifstream in(filename, std::ios::binary);
		if (in) {
			std::string content;
			in.seekg(0, std::ios::end);
			content.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&content[0], content.size());
			in.close();
			return (content);
		}
		throw(errno);
	}
}