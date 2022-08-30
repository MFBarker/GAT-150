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
        return false;
    }
    bool Font::Load(const std::string& filename, int fontSize)
    {
        m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);

        return m_ttfFont;
    }

    SDL_Surface* Font::CreateSurface(const std::string& text, const Color& color)
    {
        // !! convert Color color to SDL_Color c 
        // !! get address of color (&) 
        // !! cast to SDL_Color 
        // !! dereference 
        SDL_Color con;
        con.r = color.r;
        con.b = color.b;
        con.g = color.g;
        con.a = color.a;

        SDL_Color c = con;
        SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, text.c_str(), c);

        // !! check if surface is nullptr, if so then LOG error 
        if (!surface)
        {
            LOG(SDL_GetError());
        }

        return surface;
    }
}
