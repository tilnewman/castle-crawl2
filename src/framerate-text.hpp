#ifndef FRAMERATETEXT_HPP_INCLUDED
#define FRAMERATETEXT_HPP_INCLUDED
//
// framerate-text.hpp
//
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

namespace castlecrawl
{
    struct Context;

    class FramerateText
    {
      public:
        FramerateText();

        void setup(const Context & context);
        void update();
        void draw(sf::RenderTarget & target, sf::RenderStates states) const;

      private:
        sf::Text m_text;
        float m_frameCounter;
        sf::Clock m_secondClock;
    };

} // namespace castlecrawl

#endif // FRAMERATETEXT_HPP_INCLUDED
