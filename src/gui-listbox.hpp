#ifndef GUILISTBOX_HPP_INCLUDED
#define GUILISTBOX_HPP_INCLUDED
//
// gui-listbox.hpp
//
#include "context.hpp"
#include "font.hpp"
#include "item.hpp"
#include "sfml-util.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>

namespace castlecrawl
{
    struct ListboxIndexes
    {
        std::size_t display{ 0 };
        std::size_t offset{ 0 };
    };

    //

    class Listbox : public sf::Drawable
    {
      public:
        Listbox(const std::vector<item::Item> & t_items);

        void setup(
            const Context & t_context,
            const FontSize t_fontSize,
            const std::size_t t_widthCharsMax,
            const std::size_t t_heightRows);

        [[nodiscard]] inline bool empty() const { return m_items.empty(); }
        [[nodiscard]] inline bool getFocus() const { return m_hasFocus; }

        void setFocus(const bool t_hasFocus)
        {
            m_hasFocus = t_hasFocus;
            redraw();
        }

        [[nodiscard]] std::size_t selectedIndex() const
        {
            return (m_indexes.display + m_indexes.offset);
        }

        [[nodiscard]] sf::FloatRect getGlobalBounds() const
        {
            return m_bgRectangle.getGlobalBounds();
        }

        void setPosition(const sf::Vector2f & t_pos);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;
        bool selectNext();
        bool selectPrev();
        void redraw();

      private:
        const std::vector<item::Item> & m_items;
        bool m_hasFocus;
        std::size_t m_rowCount;
        const sf::Color m_highlightColor;
        sf::RectangleShape m_bgRectangle;
        ListboxIndexes m_indexes;
        std::vector<sf::FloatRect> m_rowRects;
        std::vector<sf::Vertex> m_rowLineVerts;
        std::vector<sf::Text> m_rowTexts;
        sf::RectangleShape m_selectionRectangle;
        sf::RectangleShape m_guideRectangle;
    };

} // namespace castlecrawl

#endif // GUILISTBOX_HPP_INCLUDED
