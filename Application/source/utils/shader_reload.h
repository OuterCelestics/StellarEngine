#pragma once

#include "engine.h"

namespace Editor::Utils
{
	using namespace Engine;

	class ShaderReload
	{
	public:
		ShaderReload(Shaders* shader);
	private:
		Shaders* m_Shader = nullptr;
	};
}

