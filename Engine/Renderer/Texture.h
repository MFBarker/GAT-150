#pragma once 
#include "..\Math\Vector2.h" 
#include <string> 

struct SDL_Texture;

namespace neu
{
	
	class Texture
	{
		friend class Renderer;

	public:
		Texture() = default;
		~Texture();

		bool Create(neu::Renderer& renderer , const std::string& filename);

		Vector2 GetSize() const;

	private:
		SDL_Texture* m_texture = nullptr;
	};
}
