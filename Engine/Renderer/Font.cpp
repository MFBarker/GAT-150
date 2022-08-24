#include "Font.h"

namespace neu
{
    neu::Font::Font(const std::string& filename, int fontSize)
    {
    }

    Font::~Font()
    {
        if (m_ttfFont)
        {
            //TTF_CloseFont
        }
    }

    bool Font::Create(const std::string name, ...)
    {
        return false;
    }
    bool Font::Load(const std::string& filename, int fontSize)
    {
        return false;
    }
}
