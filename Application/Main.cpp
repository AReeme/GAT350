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

	glm::vec3 pos = {0,0,0};

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
			actor->m_transform.position = pos;
		}
		auto actor2 = scene->GetActorFromName("Ogre");
		if (actor2)
		{
			//actor2->m_transform.rotation.y += neu::g_time.deltaTime * 60.0f;
		}
		auto actor3 = scene->GetActorFromName("Light2");
		auto actor4 = scene->GetActorFromName("Light3");


		ImGui::Begin("Hello!");
		ImGui::Button("Press Me!");
		ImGui::SliderFloat3("Position", &pos[0], -5.0f, 5.0f);
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

