#pragma once

#include "Serialization/JSON.h"

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"
#include "Core/Logger.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"

#include "Components/PlayerComponents.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponents.h"
#include "Components/PhysicsComponents.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/ModelComponents.h"
#include "Components/SprAnimComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/TilemapComponent.h"

#include "Math/MathUtils.h" // alternate "../Engine/Math/MathUtils.h"
#include "Math/Random.h"

#include "Input/InputSystems.h"
#include "Audio/AudioSystems.h"
#include "Resource/ResourceManager.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"

#include "Physics/PhysicsSystem.h"

#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <memory>

namespace neu
{
	extern InputSystem g_inputSystem;
	extern Time g_time;
	extern Renderer g_renderer;
	extern AudioSystem g_audioSystem;
	extern ResourceManager g_resources;
	extern PhysicsSystem g_physicsSystem;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();
	};
}