#ifndef GUISTATBAR_HPP_INCLUDED
#define GUISTATBAR_HPP_INCLUDED
//
// gui-stat-bar.hpp
//
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace castlecrawl
{
    struct Context;

    //

    class StatBar : public sf::Drawable
    {
      public:
        StatBar();

        void setup(
            const Context & t_context,
            const sf::FloatRect & t_region,
            const sf::Color & t_color,
            const int t_currentValue,
            const int t_maxValue);

        void setCurrentValue(const Context & t_context, const int t_newValue);
        void setMaxValue(const Context & t_context, const int t_newValue);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

        [[nodiscard]] inline const sf::FloatRect bounds() const
        {
            return m_outerRectangle.getGlobalBounds();
        }

      private:
        void update(const Context & t_context);

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
