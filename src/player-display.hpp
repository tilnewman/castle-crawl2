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

        void setup(const Context & t_context);
        [[nodiscard]] MapPos_t position() const { return m_mapPos; }
        void position(const Context & t_context, const MapPos_t & t_newPosition);
        void update(const Context & t_context, const float t_frameTimeSec);
        inline void shake() { m_isShaking = true; }
        void bloodSplatStart(const Context & t_context);
        void bloodSplatStop() { m_splatTimeSec = 0.0f; }

        void draw(const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states)
            const;

      private:
        MapPos_t m_mapPos;
        sf::Vector2f m_screenPos;
        sf::Sprite m_sprite;

        bool m_isShaking;
        float m_shakeTimeSec;
        Shaker m_shaker;

        float m_splatTimeSec;
        sf::Sprite m_splatSprite;
    };

} // namespace castlecrawl

#endif // PLAYER_HPP_INCLUDED
