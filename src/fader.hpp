#ifndef CASTLECRAWL2_FADER_HPP_INCLUDED
#define CASTLECRAWL2_FADER_HPP_INCLUDED
//
// fader.hpp
//
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace castlecrawl2
{
    class Fader
    {
      public:
        Fader();

        void reset();

        void setup(
            const bool isFadingIn,
            const sf::Color & color,
            const float durationSec,
            const sf::FloatRect & rect);

        // returns true only if the update transitioned from isFading() to !isFading()
        bool update(const float frameTimeSec);

        void draw(sf::RenderTarget & target, sf::RenderStates states) const;
        bool isFading() const { return (m_timerSec < m_durationSec); }
        bool isFadingIn() const { return m_isFadingIn; }

      private:
        bool m_isFadingIn;
        sf::RectangleShape m_rectangle;
        float m_timerSec;
        float m_durationSec;
        sf::Color m_fadeColor;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_FADER_HPP_INCLUDED
