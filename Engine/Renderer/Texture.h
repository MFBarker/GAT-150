#pragma once 
#include "Math/Vector2.h" 
#include "Resource/Resource.h" 
#include <string> 

struct SDL_Texture;

namespace neu
{
	class Renderer;
	
	class Texture : public Resource
	{
		friend class Renderer;

	public:
		Texture() = default;
		~Texture();

		bool Create(const std::string name, ...) override;
		bool Create(neu::Renderer& renderer , const std::string& filename);

		Vector2 GetSize() const;

		SDL_Texture* m_texture = nullptr;
	private:
	};
}
