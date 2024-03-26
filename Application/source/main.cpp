#include <engine.h>
#include <iostream>
#include <Windows.h>
#include <glad/glad.h>

using namespace std;

#define SHARED_MEM_NAME L"shader_shared_mem"
#define SHARED_MEM_SIZE 12288

class Source : public Engine::Application
{
private:
    bool loadShaderBinary(GLuint program) {
        // Open shared memory
        HANDLE hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, SHARED_MEM_NAME);
        if (hMapFile == NULL) {
            std::cerr << "Failed to open file mapping object: " << GetLastError() << std::endl;
            return false;
        }

        // Map shared memory into the address space of the process
        LPVOID shared_memory = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, SHARED_MEM_SIZE);
        if (shared_memory == NULL) {
            std::cerr << "Failed to map view of file: " << GetLastError() << std::endl;
            CloseHandle(hMapFile);
            return false;
        }

        // Read binary data from shared memory
        GLint length = 0;
        glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &length);

        GLint formats = 0;
        glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
        if (formats < 1) {
            std::cerr << "Driver does not support any binary formats." << std::endl;
            exit(EXIT_FAILURE);
        }

        // Read binary data from shared memory
        std::vector<char> buffer(sizeof(shared_memory));
        GLenum format = 0;

        // Install shader binary
        glProgramBinary(program, format, buffer.data(), buffer.size());

        std::cout << "length: " << length << " format: " << format << std::endl;
        // Unmap shared memory
        UnmapViewOfFile(shared_memory);
        CloseHandle(hMapFile);

        // Check for success/failure
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (GL_FALSE == status) {
            std::cerr << "Failed to link shader program from binary." << std::endl;
            return false;
        }

        return true;
    }

public:
    Source() : Application()
    {
        if (gladLoadGL())
        {
            GLuint program = glCreateProgram();
            std::cout << "OpenGL loaded successfully" << std::endl;

            if (!loadShaderBinary(program)) {
                std::cerr << "Failed to load shader program from shared memory" << std::endl;
            }
            else {
                std::cout << "Shader program loaded successfully" << std::endl;
            }
        }
        else
        {
            std::cerr << "Failed to load OpenGL" << std::endl;
        }
    }

    ~Source()
    {

    }
};

Engine::Application* Engine::CreateApplication()
{
    return new Source();
}