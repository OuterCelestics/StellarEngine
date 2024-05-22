#pragma once

#include "engine.h"
#include "utils/shader_reload.h"

using namespace Engine;

namespace Editor
{
	class Editor : public Layer
	{
	public:
		Editor(Application* app);
		virtual ~Editor() = default;

		// Inherited via Layer
		void OnAttach() override;
		void OnInput() override;
		void OnUpdate() override;
		void OnRender() override;
		void OnDetach() override;

	private:
		Utils::ShaderReload* reload = nullptr;
		InputEvent* m_Input = nullptr;
		WindowManager* m_Window = nullptr;
		Camera* m_MainCamera = nullptr;
		Shaders* m_Shader = nullptr;
		Scene* m_ActiveScene = nullptr;
	private:
		float speed = 0.01f;
	};
}