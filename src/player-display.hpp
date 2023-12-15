#ifndef PLAYERDISPLAY_HPP_INCLUDED
#define PLAYERDISPLAY_HPP_INCLUDED
//
// player-display.hpp
//
#include "map-types.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace castlecrawl
{
    struct Context;

    class PlayerDisplay
    {
      public:
        PlayerDisplay();

        void setup(const Context & context);
        const MapPos_t position() const { return m_position; }
        void position(const Context & context, const MapPos_t & newPosition);

        void
            draw(const Context & context, sf::RenderTarget & target, sf::RenderStates states) const;

      private:
        MapPos_t m_position;
        sf::Sprite m_sprite;
    };

} // namespace castlecrawl

#endif // PLAYER_HPP_INCLUDED