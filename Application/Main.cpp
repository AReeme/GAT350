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

	neu::g_renderer.CreateWindow("Neumont", 1000, 600);
	LOG("Window Created...");

	// load scene 
	auto scene = neu::g_resources.Get<neu::Scene>("scenes/texture.scn");

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		auto actor1 = scene->GetActorFromName("Spot");
		if (actor1)
		/*{
			actor1->m_transform.rotation.y += neu::g_time.deltaTime * 90.0f;
		}*/

		auto actor2 = scene->GetActorFromName("Ogre");
		/*if (actor2)
		{
			actor2->m_transform.rotation.y += neu::g_time.deltaTime * 90.0f;
		}*/
		
		auto material = neu::g_resources.Get<neu::Material>("Materials/Multi.mtrl");
		if (material)
		{
			//material->uv_offset += glm::vec2(neu::g_time.deltaTime);
		}

		scene->Update();

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	}

	scene->RemoveAll();

	neu::Engine::Instance().Shutdown();

	return 0;
}

