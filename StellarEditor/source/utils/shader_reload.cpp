#include "shader_reload.h"
#include <iostream>

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

			std::cout << "Shader is re-activated" << std::endl;
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

	void ShaderReload::CheckForShaderUpdate()
	{
		std::filesystem::file_time_type newModifiedTime = std::filesystem::last_write_time("shaders/default.frag");

		if (newModifiedTime > m_shaderModifiedTime)
		{
			std::cout << "Shader updated... reloading shader..." << std::endl;
			m_shaderModifiedTime = newModifiedTime;
			ShaderReload::Bind();
			ShaderReload::Reload();

		}
	}
}
