#include <engine.h>
#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
using namespace std;

class Source : public Engine::Application
{
public:
	Source() : Application()
	{
        HANDLE hMapFile;
        LPVOID pBuf;

        // Open the file mapping
        hMapFile = OpenFileMapping(
            FILE_MAP_READ,
            FALSE,
            L"shader_hot_reload_address");

        if (hMapFile == NULL) {
            cerr << "Could not open file mapping object (" << GetLastError() << ")." << endl;
        }

        // Map the shared memory into the process's address space
        pBuf = MapViewOfFile(
            hMapFile,
            FILE_MAP_READ,
            0,
            0,
            0); // Let the function determine the size of the memory region

        if (pBuf == NULL) {
            cerr << "Could not map view of file (" << GetLastError() << ")." << endl;

            CloseHandle(hMapFile);
        }

        // Get the size of the memory region pointed to by pBuf
        MEMORY_BASIC_INFORMATION memInfo;
        if (VirtualQuery(pBuf, &memInfo, sizeof(memInfo)) == 0) {
            cerr << "VirtualQuery failed (" << GetLastError() << ")." << endl;

            UnmapViewOfFile(pBuf);
            CloseHandle(hMapFile);
        }

        // Actual size of the memory region
        SIZE_T dataSize = memInfo.RegionSize;

        gladLoadGL(); // Load the OpenGL functions
        // Example: Assuming glProgramBinary() is used to set the binary shader data
        GLenum binaryFormat;
        GLuint programID = glCreateProgram();
        // Set the binary data to the program object
        glProgramBinary(programID, binaryFormat, static_cast<const void*>(pBuf), dataSize);
        GLint success;
        char infoLog[512];
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programID, 512, nullptr, infoLog);
            std::cerr << "Failed to link program: " << infoLog << std::endl;
        }

        // Unmap the shared memory
        UnmapViewOfFile(pBuf);

        // Close the file mapping handle
        CloseHandle(hMapFile);

	}

	~Source()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Source();
}