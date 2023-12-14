#ifndef CASTLECRAWL2_TOPPANEL_HPP_INCLUDED
#define CASTLECRAWL2_TOPPANEL_HPP_INCLUDED
//
// top-panel.hpp
//
#include "state.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl2
{
    struct Context;

    class TopPanel
    {
      public:
        TopPanel();

        void setup(const Context & context);

        void
            draw(const Context & context, sf::RenderTarget & target, sf::RenderStates states) const;

      private:
        sf::Texture m_titleTexture;
        sf::Sprite m_titleSprite;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_TOPPANEL_HPP_INCLUDED
