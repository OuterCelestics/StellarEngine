#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <glad/glad.h>

#include "tools/context.h"

#define SHARED_MEM_NAME L"shader_shared_mem"
#define SHARED_MEM_SIZE 12288

std::string read_file(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer(size, '\0');
    file.read(&buffer[0], size);
    file.close();

    return buffer;
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
        return 0;
    }
    return shader;
}

int main(int argc, char* argv[]) {
    // Initialize OpenGL context
    // (Make sure to have a valid OpenGL context before calling any OpenGL functions)
    // ...

    Context* context = new Context();
    context->initialize();
    if (gladLoadGL() == 0) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    if (argc != 3) {
        std::cerr << "Usage: ShaderCompileWorker <vertex_shader> <fragment_shader>\n" << std::endl;
        std::cerr << "Example: ShaderCompileWorker shader.vert fragment.frag\n" << std::endl;
        return -1;
    }


    GLuint program = glCreateProgram();
    // Compile vertex shader
    GLuint vertex_shader = compileShader(argv[1], GL_VERTEX_SHADER);
    if (!vertex_shader) {
        std::cerr << "Error during vertex shader compilation" << std::endl;
        return -1;
    }

    // Compile fragment shader
    GLuint fragment_shader = compileShader(argv[2], GL_FRAGMENT_SHADER);
    if (!fragment_shader) {
        std::cerr << "Error during fragment shader compilation" << std::endl;
        return -1;
    }

    // Attach the shaders to the program
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    // Link the program
    glLinkProgram(program);

    // Check if the program linked successfully
    GLint success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Failed to link program: " << infoLog << std::endl;
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteProgram(program);
        return 1;
    }

    GLint formats = 0;
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
    if (formats < 1) {
        std::cerr << "Driver does not support any binary formats." << std::endl;
        return false;
    }

    GLint length = 0;

    glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &length);

    std::vector<GLubyte> buffer(length);
    GLenum format = 0;
    glGetProgramBinary(program, length, NULL, &format, buffer.data());

    std::string fName("shader.bin");
    std::cout << "Writing to " << fName << ", binary format = " << format << std::endl;
    std::ofstream out(fName.c_str(), std::ios::binary);
    out.write(reinterpret_cast<char*>(buffer.data()), length);
    out.close();
}
