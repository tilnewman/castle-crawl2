#ifndef MOUSEOVER_HPP_INCLUDED
#define MOUSEOVER_HPP_INCLUDED
//
// mouseover.hpp
//
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

namespace castlecrawl
{
    struct Context;

    class Mouseover
    {
      public:
        Mouseover();

        void reset();

        void update(const Context & t_context, const float t_frameTimeSec);

        void handleMouseMovedEvent(const sf::Vector2i & t_newPos);

        void draw(const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states)
            const;

      private:
        void setupDisplay(const Context & t_context);

      private:
        sf::Clock m_clock;
        bool m_willDisplay;
        sf::Vector2i m_mousePos;
        sf::Text m_text;
    };

} // namespace castlecrawl

#endif // MOUSEOVER_HPP_INCLUDED
