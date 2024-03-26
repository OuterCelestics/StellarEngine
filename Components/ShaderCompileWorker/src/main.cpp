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

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint formats = 0;
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
    if (formats < 1) {
        std::cerr << "Driver does not support any binary formats." << std::endl;
        return false;
    }

    // Get the binary length
    GLint length = 0;
    glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &length);

    // Retrieve the binary code
    std::vector<GLubyte> buffer(length);
    GLenum format = 0;
    glGetProgramBinary(program, length, NULL, &format, buffer.data());

    // Create or open shared memory
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, length, SHARED_MEM_NAME);
    if (hMapFile == NULL) {
        std::cerr << "Failed to create file mapping object: " << GetLastError() << std::endl;
        return false;
    }

    // Map shared memory into the address space of the process
    LPVOID shared_memory = MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, length);
    if (shared_memory == NULL) {
        std::cerr << "Failed to map view of file: " << GetLastError() << std::endl;
        CloseHandle(hMapFile);
        return false;
    }

    std::cout << "length: " << length << std::endl;
    std::cout << "Binary format: " << format << std::endl;

    // Copy the binary data to shared memory
    std::memcpy(shared_memory, buffer.data(), length);
    std::cout << "Shader binary copied to shared memory" << std::endl;

    Sleep(50000);
    std::cout << "ShaderCompileWorker finished" << std::endl;
    // Unmap shared memory
    UnmapViewOfFile(shared_memory);

    // Close shared memory handle
    CloseHandle(hMapFile);

    // Clean up OpenGL resources
    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);

    return 0;
}