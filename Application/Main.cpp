#include "Engine.h" 
#include <iostream> 

int main(int argc, char** argv)
{
	neu::InitializeMemory();

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	neu::g_renderer.CreateWindow("Neumont", 800, 600);

	float angle = 0;
	neu::Vector2 position;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		neu::g_renderer.BeginFrame();

		if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::KeyState::Held)
		{
			position.x -= neu::g_time.deltaTime;
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held)
		{
			position.x += neu::g_time.deltaTime;
		}
		angle += 90.0f * neu::g_time.deltaTime;

		glPushMatrix();

		//glScalef(0.5f, 0.5f, 0.5f);
		//glRotatef(angle, 0, 0, 1);
		glTranslatef(position.x, position.y, 0);

		glBegin(GL_TRIANGLES);


		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);
		//glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		//glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);

		glEnd();

		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();

	return 0;
}

