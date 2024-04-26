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
		void CheckForShaderUpdate(std::string vertexfName, std::string fragmentfName);

	private:
		Shaders* m_Shader = nullptr;
		Shaders* m_ReloadedShader = nullptr;

		std::filesystem::file_time_type m_modified_frag = std::filesystem::last_write_time("shaders/default.frag");
		std::filesystem::file_time_type m_modified_vert = std::filesystem::last_write_time("shaders/default.vs");
	};
}

