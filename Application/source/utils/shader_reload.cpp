#include "shader_reload.h"

namespace Editor::Utils
{
	ShaderReload::ShaderReload(Shaders* shader)
	{
		m_Shader = shader;

		if (m_Shader != nullptr)
		{
			std::cout << "Shader is not null" << std::endl;
		}
		else
		{
			std::cout << "Shader is null" << std::endl;
		}
	}
}
