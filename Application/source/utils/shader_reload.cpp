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
}
