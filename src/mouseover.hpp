#ifndef CASTLECRAWL2_MOUSEOVER_HPP_INCLUDED
#define CASTLECRAWL2_MOUSEOVER_HPP_INCLUDED
//
// mouseover.hpp
//
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

namespace castlecrawl2
{
    struct Context;

    class Mouseover
    {
      public:
        Mouseover();

        void reset();

        void update(const Context & context, const float frameTimeSec);

        void handleMouseMovedEvent(const sf::Vector2i & newPos);

        void
            draw(const Context & context, sf::RenderTarget & target, sf::RenderStates states) const;

      private:
        void setupDisplay(const Context & context);

      private:
        sf::Clock m_clock;
        bool m_willDisplay;
        sf::Vector2i m_mousePos;
        sf::Text m_text;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_MOUSEOVER_HPP_INCLUDED
