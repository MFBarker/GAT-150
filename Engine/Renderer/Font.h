#pragma once
#include "Resource/Resource.h"
#include <string>

struct _TTF_Font;

namespace neu
{
	class Font : public Resource
	{
	public:
		//FOnt() =default
		//Font(string& filename, int fontSize);
		//~Font();

		bool Create(const std::string& name, ...) override;
		//void load

		friend class Text;
	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}