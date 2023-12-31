#ifndef GUISTATBAR_HPP_INCLUDED
#define GUISTATBAR_HPP_INCLUDED
//
// gui-stat-bar.hpp
//
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace castlecrawl
{
    struct Context;

    class StatBar : public sf::Drawable
    {
      public:
        StatBar();

        void setup(
            const Context & context,
            const sf::FloatRect & region,
            const sf::Color & color,
            const int maxValue);

        void setCurrentValue(const Context & context, const int newValue);
        void setMaxValue(const Context & context, const int newValue);
        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

      private:
        void update(const Context & context);

      private:
        sf::Text m_text;
        sf::Color m_color;
        int m_max;
        int m_current;
        sf::RectangleShape m_outerRectangle;
        sf::RectangleShape m_innerRectangle;
    };

} // namespace castlecrawl

#endif // GUISTATBAR_HPP_INCLUDED
