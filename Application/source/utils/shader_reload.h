#pragma once

#include "engine.h"

namespace Editor::Utils
{
	using namespace Engine;

	class ShaderReload
	{
	public:
		ShaderReload(Shaders* shader);
		~ShaderReload();

		void Reload();
		void Bind();
		void Unbind();
	private:
		Shaders* m_Shader = nullptr;
		Shaders* m_ReloadedShader = nullptr;
	};
}

