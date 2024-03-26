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
        std::ifstream inputStream("shader.bin", std::ios::binary);
        std::istreambuf_iterator<char> startIt(inputStream), endIt;
        std::vector<char> buffer(startIt, endIt);  // Load file
        inputStream.close();

        GLenum format = 1;
        // Install shader binary
        glProgramBinary(program, format, buffer.data(), buffer.size());

        // Check if the loading was successful
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            GLint logLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> log(logLength);
            glGetProgramInfoLog(program, logLength, nullptr, log.data());
            std::cerr << "Failed to load program: " << log.data() << std::endl;
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