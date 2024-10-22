#include "editor.h"
#include <iostream>

namespace Editor {
	Editor::Editor(Application* app)
	{
		m_Input = app->m_Input;
		m_MainCamera = app->m_MainCamera;
		m_Window = app->m_Window;
		m_Shader = app->api->shaderProgram;
	}

	void Editor::OnAttach()
	{
		reload = new Utils::ShaderReload(m_Shader);
		m_ActiveScene = new Scene();

		// create a new entity
		auto entity = m_ActiveScene->CreateEntity("Test Entity");
		entity.AddComponent<MeshRendererComponent>();

		// manipulate the entity
		if (entity)
		{
			auto& mesh = entity.GetComponent<MeshRendererComponent>();

			// TODO: load a mesh and shader from file
			/*mesh.mesh = new Mesh("assets/models/cube.obj");
			mesh.shader = new Shader("shaders/default.vs", "shaders/default.frag");*/

			std::cout << "Entity tag: " << entity.GetComponent<TagComponent>().Tag << std::endl;
		}
	}

	void Editor::OnInput()
	{
		// input bindings
		m_Input->BindAction("escape", [this]()
		{
			m_Window->CaptureMouse(false);
		});

		m_Input->BindAction("forward", [this]()
		{
			m_MainCamera->MoveCamera(FORWARD, speed);
		});

		m_Input->BindAction("backwards", [this]()
		{
			m_MainCamera->MoveCamera(BACKWARD, speed);
		});

		m_Input->BindAction("left", [this]()
		{
			m_MainCamera->MoveCamera(LEFT, speed);
		});

		m_Input->BindAction("right", [this]()
		{
			m_MainCamera->MoveCamera(RIGHT, speed);
		});

		m_Input->BindAction("e", [this]()
		{
			m_MainCamera->MoveCamera(UP, speed);
		});

		m_Input->BindAction("q", [this]()
		{
			m_MainCamera->MoveCamera(DOWN, speed);
		});
	}

	void Editor::OnUpdate()
	{
		try
		{
			reload->CheckForShaderUpdate("shaders/default.vs", "shaders/default.frag");
		}
		catch (const std::exception&)
		{
			Debug::ErrorLog("Error in Editor::OnUpdate()", false);
		}
	}

	void Editor::OnRender()
	{

	}

	void Editor::OnDetach()
	{

	}
}