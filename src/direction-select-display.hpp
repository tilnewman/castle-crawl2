#ifndef DIRECTIONSELECTDISPLAY_HPP_INCLUDED
#define DIRECTIONSELECTDISPLAY_HPP_INCLUDED
//
// direction-select-display.hpp
//
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{
    struct Context;

    class DirectionSelectDisplay : public sf::Drawable
    {
      public:
        DirectionSelectDisplay();

        void setup(const Context & t_context);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

      private:
        sf::RectangleShape m_topRectangle;
        sf::RectangleShape m_botRectangle;
        sf::RectangleShape m_leftRectangle;
        sf::RectangleShape m_rightRectangle;
    };

} // namespace castlecrawl

#endif // DIRECTIONSELECTDISPLAY_HPP_INCLUDED
