#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

#include "tools/context.h"
#include "tools/accesor.h"
#include "tools/config.h"

std::string read_file(const std::string& filePath) {
	std::ifstream file(filePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint compileShader(const char* shader_path, GLenum shader_type) {
	GLuint shader = glCreateShader(shader_type);

	std::string shader_code = read_file(shader_path);
	const char* shader_code_array[] = { shader_code.c_str() };

	glShaderSource(shader, 1, shader_code_array, NULL);
	glCompileShader(shader);

	// Check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	return shader;
}

int main(int argc, char* argv[]) {
	Context* context = new Context();

	Accesor* accesor = new Accesor();
	Config* config = new Config("config", "scw.ini");
	context->initialize();

	accesor->buffer_size = config->GetInteger("general", "buffer_size");

	if (!gladLoadGL()) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	if (argc != 3) {
		std::cerr << "Usage: ShaderCompileWorker <vertex_shader> <fragment_shader>\n" << std::endl;
		std::cerr << "Example: ShaderCompileWorker shader.vert fragment.frag\n" << std::endl;
		return -1;
	}

	// Compile vertex shader
	GLuint vertex_shader = compileShader(argv[1], GL_VERTEX_SHADER);
	if (vertex_shader == 0) {
		glDeleteShader(vertex_shader);
		return 1; // Error during vertex shader compilation
	}

	// Compile fragment shader
	GLuint fragment_shader = compileShader(argv[2], GL_FRAGMENT_SHADER);
	if (fragment_shader == 0) {
		glDeleteShader(fragment_shader);
		return 1; // Error during fragment shader compilation
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	// Check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	int length = 0;
	glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &length);
	if (length < 1) {
		std::cerr << "No binary length available" << std::endl;
		return -1;
	}

	int formats = 0;
	glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
	if (formats < 1) {
		std::cerr << "No binary formats available" << std::endl;
		return -1;
	}

	std::vector<char> binary(length);
	GLenum format;
	glGetProgramBinary(program, length, NULL, &format, binary.data());

	// Convert the char vector to a GLubyte vector
	std::vector<GLubyte> binaryGLubyte(binary.begin(), binary.end());

	std::cout << "binary size: " << binaryGLubyte.size() << std::endl;

	if (accesor->initialize()) {
		accesor->write(binaryGLubyte, config->GetInteger("general", "delay"));
		std::cout << "Binary written!" << std::endl;
	}

	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteProgram(program);

	return 0;
}