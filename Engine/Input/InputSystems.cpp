#include "InputSystems.h"
#include <SDL.h>
#include <iostream>

namespace neu
{
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_UP;
	const uint32_t key_down = SDL_SCANCODE_DOWN;
	const uint32_t key_left = SDL_SCANCODE_LEFT;
	const uint32_t key_right = SDL_SCANCODE_RIGHT;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;
	const uint32_t key_enter = SDL_SCANCODE_RETURN;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;
	}

	void InputSystem::Shutdown()
	{
		//
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//save previous state
		m_prevKeyboardState = m_keyboardState;

		//get current state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());


		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = neu::Vector2{ (float) x , (float) y };
		
	}

	InputSystem::State InputSystem::GetButtonState(uint32_t button)
	{
		InputSystem::State state = InputSystem::State::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		// set the keyState if buttonDown (true) and prevButtonDown (true) 
		// fill in the remaining states 
		if (buttonDown == true && prevButtonDown == true)
		{
			state = State::Held;
		}
		else if (buttonDown == true && prevButtonDown == false)
		{
			state = State::Released;
		}
		else if (buttonDown == false && prevButtonDown == true)
		{
			state = State::Pressed;
		}
		else if (buttonDown == false && prevButtonDown == false)
		{
			state = State::Idle;
		}

		return state;
	}
}

