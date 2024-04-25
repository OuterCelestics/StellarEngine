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
		void CheckForShaderUpdate();

	private:
		Shaders* m_Shader = nullptr;
		Shaders* m_ReloadedShader = nullptr;
		std::filesystem::file_time_type m_shaderModifiedTime = std::filesystem::last_write_time("shaders/default.frag");
	};
}

