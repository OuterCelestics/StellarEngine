#include "shader_reload.h"

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
			std::cout << "Shader is invalid" << std::endl;
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
}
