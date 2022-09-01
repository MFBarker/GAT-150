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
    bool Texture::Create(const std::string name, ...)
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

        if (m_texture == nullptr)
        {
            LOG("SDL ERROR(Texture::Create): %s",SDL_GetError());
            return false;
        }

        SDL_FreeSurface(surface);
        return true;
    }

    bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer)
    {
        // destroy the current texture if one exists 
        if (m_texture) SDL_DestroyTexture(m_texture);

        // create texture 
        // !! call SDL_CreateTextureFromSurface passing in renderer and surface 
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer,surface);

        if (surface == nullptr)
        {
            LOG("Error Loading Surface %s");
            SDL_FreeSurface(surface);
            return false;
        }

       if (m_texture == nullptr)
       {
                LOG("Texture::Create from surface (m_texture = null)", SDL_GetError());
                return false;
       }

       SDL_FreeSurface(surface);
        return true;
    }

    Vector2 Texture::GetSize() const
    {
        SDL_Point point;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x , &point.y);

        return Vector2((float)point.x, (float)point.y);
    }
}
