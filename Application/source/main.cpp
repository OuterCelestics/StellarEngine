#include <engine.h>
#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <thread>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;
using namespace std;

class Source : public Engine::Application
{
public:
    Source() : Application() {
        
    }

    ~Source() {}

    void StartMonitoring(const std::string& filePath) {
        // Pass 'this' as an argument to the thread constructor
        monitorThread = std::thread(&Source::MonitorFile, this, filePath);
        // Detach the thread so it can run independently
        monitorThread.detach();
    }

private:
    std::thread monitorThread;
    std::string shaderFilePath; // private variable needed by OnFileChange

    // Function to monitor file changes
    void MonitorFile(const std::string& filePath)
    {
        shaderFilePath = filePath; // Store the file path in a private variable

        // Get the last modification time of the file
        auto lastWriteTime = fs::last_write_time(filePath);

        while (true) {
            // Check if the file has been modified
            if (fs::last_write_time(filePath) != lastWriteTime) {
                // If modified, call the callback function
                OnFileChange(filePath);
                // Update the last modification time
                lastWriteTime = fs::last_write_time(filePath);
            }
            // Sleep for a short duration before checking again
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    // Member function to handle file change event
    void OnFileChange(const std::string& filePath) {
        // Access private members as needed
        std::cout << "Shader file " << shaderFilePath << " has been changed!" << std::endl;
        auto shader = api->getShaderProgram();
        shader->DetachShader();
        shader->Delete();

        try
        {
            // Recompile the shader
            shader->Compile("shaders/default.vs", "shaders/default.frag");
            shader->Activate();

            // We need to to get these values from the EngineDLL

            // shader->setMat4("projection", projection);
            // shader->setMat4("view", view);
            // textureID.Bind();
            // VAO1->Bind();
        }
        catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};

Engine::Application* Engine::CreateApplication()
{
    Source* app = new Source();
    app->StartMonitoring("shaders/default.frag");
    return app;
}
