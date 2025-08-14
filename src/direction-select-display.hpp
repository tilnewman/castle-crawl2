#ifndef DIRECTIONSELECTDISPLAY_HPP_INCLUDED
#define DIRECTIONSELECTDISPLAY_HPP_INCLUDED
//
// direction-select-display.hpp
//
#include "value-bouncer.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{
    struct Context;

    class DirectionSelectDisplay : public sf::Drawable
    {
      public:
        DirectionSelectDisplay();

        void setup(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

      private:
        sf::RectangleShape m_topRectangle;
        sf::RectangleShape m_botRectangle;
        sf::RectangleShape m_leftRectangle;
        sf::RectangleShape m_rightRectangle;
        sf::Texture m_arrowTexture;
        sf::Sprite m_arrowSpriteUp;
        sf::Sprite m_arrowSpriteDown;
        sf::Sprite m_arrowSpriteLeft;
        sf::Sprite m_arrowSpriteRight;
        ValueBouncer<uint8_t> m_alphaBouncer;
    };

} // namespace castlecrawl

#endif // DIRECTIONSELECTDISPLAY_HPP_INCLUDED
