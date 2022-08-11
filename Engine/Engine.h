#pragma once
#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"

#include "Components/PlayerComponents.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponents.h"
#include "Components/PhysicsComponents.h"
#include "Components/ModelComponents.h"

#include "Math/MathUtils.h" // alternate "../Engine/Math/MathUtils.h"
#include "Math/Random.h"

#include "Input/InputSystems.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"

#include "Audio/AudioSystems.h"

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
}