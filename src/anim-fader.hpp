#ifndef ANIM_FADER_HPP_INCLUDED
#define ANIM_FADER_HPP_INCLUDED
//
// anim-fader.hpp
//
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace castlecrawl
{
    class Fader
    {
      public:
        Fader();

        void reset();

        void setup(
            const bool t_isFadingIn,
            const sf::Color & t_color,
            const float t_durationSec,
            const sf::FloatRect & t_rect);

        // returns true only if the update transitioned from isFading() to !isFading()
        bool update(const float t_elapsedSec);

        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        [[nodiscard]] inline bool isFading() const { return (m_timerSec < m_durationSec); }
        [[nodiscard]] inline bool isFadingIn() const { return m_isFadingIn; }

      private:
        bool m_isFadingIn;
        sf::RectangleShape m_rectangle;
        float m_timerSec;
        float m_durationSec;
        sf::Color m_fadeColor;
    };

} // namespace castlecrawl

#endif // ANIM_FADER_HPP_INCLUDED
