#include "Engine.h"

namespace neu
{
	Renderer g_renderer;
	AudioSystem g_audioSystem;
	InputSystem g_inputSystem;
	Time g_time;
	ResourceManager g_resources;


	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
	}
}