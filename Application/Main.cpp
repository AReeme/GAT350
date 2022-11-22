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

	// create framebuffer texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(512, 512);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	// create framebuffer
	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	// load scene 
	auto scene = neu::g_resources.Get<neu::Scene>("scenes/rtt.scn");

	glm::vec3 rot = {0,0,0};
	float interpolation = 0;
	float ri = 1.4;
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

		auto program = neu::g_resources.Get<neu::Program>("shaders/fx/reflect_refract.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("interpolation", interpolation);
			program->SetUniform("ri", ri);
		}

		ImGui::Begin("Hello!");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::SliderFloat("ri", &ri, 1, 3);
		ImGui::SliderFloat("interpolation", &interpolation, 0, 1);
		ImGui::End();

		scene->Update();

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

		// render pass 1 (render to framebuffer)
		glViewport(0, 0, 512, 512);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		{
			auto actor = scene->GetActorFromName("RTT");
			if (actor)
			{
				actor->SetActive(true);
			}
		}

		// render pass 2 (render to screen)
		glViewport(0, 0, 800, 600);
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

