#include "Texture.h" 
#include "Renderer.h" 
#include "Core/Logger.h" 
#include <SDL.h> 
#include <SDL_image.h> 
#include <stdarg.h>

namespace neu
{
    Texture::~Texture()
    {
        // !! if texture not null SDL_DestroyTexture 
        
        if(m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
        }
        
    }
    bool Texture::Create(const std::string& name, ...)
    {
        //
        va_list args;

        va_start(args, name);

        Renderer& renderer = va_arg(args , Renderer);

        va_end(args);

        return Create(renderer, name);
    }

    bool Texture::Create(neu::Renderer& renderer, const std::string& filename)
    {
        // load surface 
        SDL_Surface* surface = IMG_Load(filename.c_str());// !! call IMG_Load with c-string of filename 
        Texture::m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

        //error check
        if (surface == nullptr)
        {
            LOG("Error Loading %s", filename.c_str());
            SDL_FreeSurface(surface);
            return false;
        }

        SDL_FreeSurface(surface);
        return true;
    }

    neu::Vector2 Texture::GetSize() const
    {
        SDL_Point point;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x , &point.y);

        return Vector2((float)point.x, (float)point.y);
    }
}
