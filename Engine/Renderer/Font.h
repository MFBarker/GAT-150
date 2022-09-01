#pragma once
#include "Resource/Resource.h"
#include "Math/Color.h"
#include <string>

struct _TTF_Font;
struct SDL_Surface;

namespace neu
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(const std::string name, ...) override;
		
		bool Load(const std::string& filename, int fontSize);
		SDL_Surface* CreateSurface(const std::string& text, const Color& color);

		friend class Text;
		friend class TextComponent;
	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}