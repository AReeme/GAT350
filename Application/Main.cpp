#include "Engine.h"
#include <iostream> 
#include <Renderer/Program.cpp>

int main(int argc, char** argv)
{
	LOG("Application Started...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Initialized...");

	neu::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Created...");
	neu::g_gui.Initialize(neu::g_renderer);

	// load scene 
	auto scene = neu::g_resources.Get<neu::Scene>("scenes/cubemap.scn");

	glm::vec3 rot = {0,0,0};
	float ri = 1;
	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave 
			actor->m_transform.position = rot;
		}
		auto actor2 = scene->GetActorFromName("Ogre");
		if (actor2)
		{
			actor2->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		auto actor3 = scene->GetActorFromName("Light2");
		auto actor4 = scene->GetActorFromName("Light3");

		auto program = neu::g_resources.Get<neu::Program>("shaders/fx/refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", &ri);
		}

		ImGui::Begin("Hello!");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 3);
		ImGui::End();

		scene->Update();

		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();

		neu::g_gui.EndFrame();
	}

	scene->RemoveAll();

	neu::Engine::Instance().Shutdown();

	return 0;
}

