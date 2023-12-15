#ifndef PLAYERDISPLAY_HPP_INCLUDED
#define PLAYERDISPLAY_HPP_INCLUDED
//
// player-display.hpp
//
#include "map-types.hpp"
#include "shaker.hpp"

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
        const MapPos_t position() const { return m_mapPos; }
        void position(const Context & context, const MapPos_t & newPosition);
        void update(const Context & context, const float frameTimeSec);
        void shake() { m_isShaking = true; }

        void
            draw(const Context & context, sf::RenderTarget & target, sf::RenderStates states) const;

      private:
        MapPos_t m_mapPos;
        sf::Vector2f m_screenPos;
        sf::Sprite m_sprite;
        bool m_isShaking;
        float m_shakeTimeSec;
        Shaker m_shaker;
    };

} // namespace castlecrawl

#endif // PLAYER_HPP_INCLUDED
