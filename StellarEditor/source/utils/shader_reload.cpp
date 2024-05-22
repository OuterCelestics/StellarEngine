#include "shader_reload.h"
#include <iostream>
#include <filesystem>

namespace Editor::Utils
{
	ShaderReload::ShaderReload(Shaders* shader)
	{
		m_Shader = shader;

		if (m_Shader != nullptr)
		{
			std::cout << "Shader is valid" << std::endl;
		}
		else
		{
			std::cout << "Shader is invalid" << std::endl;
		}
	}

	ShaderReload::~ShaderReload()
	{
		m_ReloadedShader->Delete();
	}

	void ShaderReload::Reload()
	{
		m_Shader->DetachShader();
		m_Shader->Delete();

		m_ReloadedShader = new Shaders();
		m_ReloadedShader->Compile("shaders/default.vs", "shaders/default.frag");
		
		if (m_ReloadedShader->ID != 0)
		{
			m_Shader = m_ReloadedShader;
			m_Shader->Activate();

			std::cout << "Shaders are re-activated" << std::endl;
		}
		else
		{
			Debug::ErrorLog("Failed to reload shader", false);
		}
	}

	void ShaderReload::Bind()
	{
		if (m_Shader->ID != 0)
		{
			std::cout << "Shader is valid" << std::endl;
		}
		else
		{
			std::cout << "Shader is invalid" << std::endl;
		}
	}

	void ShaderReload::Unbind()
	{
		m_Shader->Delete();
	}

	void ShaderReload::CheckForShaderUpdate(std::string vertexfName, std::string fragmentfName)
	{
		if (std::filesystem::exists(vertexfName) && std::filesystem::exists(fragmentfName))
		{
			std::filesystem::file_time_type modified_time_frag = std::filesystem::last_write_time(fragmentfName);
			std::filesystem::file_time_type modified_time_vert = std::filesystem::last_write_time(vertexfName);

			if (modified_time_frag > m_modified_frag || modified_time_vert > m_modified_vert)
			{
				std::cout << "shader updating..." << std::endl;
				m_modified_frag = modified_time_frag;
				m_modified_vert = modified_time_vert;

				ShaderReload::Bind();
				ShaderReload::Reload();
			}
		}
		else
		{
			Debug::ErrorLog("Vertex or fragment shader does not exist or cannot be located", true);
		}
	}
}
