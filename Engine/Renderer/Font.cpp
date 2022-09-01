#include "Font.h"
#include "Core/Logger.h"
#include <SDL_ttf.h>

namespace neu
{
    Font::Font(const std::string& filename, int fontSize)
    {
        Load(filename, fontSize);
    }

    Font::~Font()
    {
        // !! if m_ttfFont not null, close font (TTF_CloseFont) 
        if (m_ttfFont != nullptr)
        {
            TTF_CloseFont(m_ttfFont);
        }
    }

    bool Font::Create(const std::string name, ...)
    {
        Load(name, 30);

        return false;
    }
    bool Font::Load(const std::string& filename, int fontSize)
    {
        m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);

        if (m_ttfFont == nullptr)
        {
            LOG("SDL ERROR (Font::Load): %s",SDL_GetError());

        }

        return m_ttfFont;
    }

    SDL_Surface* Font::CreateSurface(const std::string& text, const Color& color)
    {
        SDL_Color c = *((SDL_Color*)(&color));
        SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, text.c_str(), c);

        if (!surface)
        {
            LOG("SDL ERROR (Font::CreateSurface): %s", SDL_GetError());
        }

        return surface;
    }
}
