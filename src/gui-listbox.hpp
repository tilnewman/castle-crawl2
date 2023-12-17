#ifndef CASTLECRAWL_GUI_LISTBOX_HPP_INCLUDED
#define CASTLECRAWL_GUI_LISTBOX_HPP_INCLUDED
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
        std::size_t display = 0;
        std::size_t offset  = 0;
    };

    //

    template <typename T>
    class Listbox : public sf::Drawable
    {
      public:
        Listbox(const std::vector<T> & items)
            : m_items(items)
            , m_hasFocus()
            , m_rowCount(0)
            , m_highlightColor(20, 20, 20, 20)
            , m_bgRectangle()
            , m_indexes()
            , m_rowRects()
            , m_rowLineVerts()
            , m_rowTexts()
            , m_selectionRectangle()
            , m_guideRectangle()
        {}

        void setup(
            const Context & context,
            const FontSize fontSize,
            const std::size_t widthCharsMax,
            const std::size_t heightRows)
        {
            m_rowCount = heightRows;

            const sf::Vector2f letterSize = context.fonts.extent(fontSize).letter_size;

            m_bgRectangle.setSize({ (letterSize.x * static_cast<float>(widthCharsMax)),
                                    (letterSize.y * static_cast<float>(heightRows)) });

            m_bgRectangle.setOutlineThickness(1.0f);

            m_rowRects.clear();
            float posTop = m_bgRectangle.getGlobalBounds().top;
            for (std::size_t i = 0; i < heightRows; ++i)
            {
                sf::FloatRect rect{ m_bgRectangle.getGlobalBounds() };

                rect.height =
                    (m_bgRectangle.getGlobalBounds().height / static_cast<float>(heightRows));

                rect.top = posTop;
                posTop += rect.height;
                m_rowRects.push_back(rect);
            }

            m_rowTexts.clear();
            for (std::size_t i = 0; i < m_rowRects.size(); ++i)
            {
                // The string "Tyjp" is used because the T char reaches high and the others reach
                // low This makes the string typical in terms of height so that the setPosition()
                // works.
                sf::Text & text = m_rowTexts.emplace_back(context.fonts.makeText(fontSize, "Tyjp"));

                // use this only to vertically center
                util::centerInside(text, m_rowRects[i]);

                text.setPosition(
                    (util::position(m_rowRects[i]).x + 1.0f), text.getGlobalBounds().top);
            }

            m_selectionRectangle.setFillColor(sf::Color(255, 255, 255, 40));
            m_selectionRectangle.setSize(util::size(m_rowRects[0]));

            m_guideRectangle.setFillColor(sf::Color::White);

            redraw();
        }

        bool empty() const { return m_items.empty(); }

        bool getFocus() const { return m_hasFocus; }

        void setFocus(const bool hasFocus)
        {
            m_hasFocus = hasFocus;
            redraw();
        }

        std::size_t selectedIndex() const { return (m_indexes.display + m_indexes.offset); }

        const sf::FloatRect getGlobalBounds() const { return m_bgRectangle.getGlobalBounds(); }

        void setPosition(const sf::Vector2f & pos)
        {
            const sf::Vector2f move{ pos - util::position(m_bgRectangle) };
            m_bgRectangle.move(move);

            for (sf::FloatRect & rect : m_rowRects)
            {
                rect.left += move.x;
                rect.top += move.y;
            }

            for (sf::Text & text : m_rowTexts)
            {
                text.move(move);
            }

            redraw();
        }

        void draw(sf::RenderTarget & target, sf::RenderStates states) const override
        {
            target.draw(&m_rowLineVerts[0], m_rowLineVerts.size(), sf::PrimitiveType::Lines);
            target.draw(m_bgRectangle, states);

            if (m_hasFocus && !m_items.empty())
            {
                target.draw(m_selectionRectangle, states);
            }

            for (const sf::Text & text : m_rowTexts)
            {
                target.draw(text, states);
            }

            if (!empty())
            {
                target.draw(m_guideRectangle, states);
            }
        }

        bool selectNext()
        {
            if (m_items.empty() || (selectedIndex() >= (m_items.size() - 1_st)))
            {
                return false;
            }

            if (m_indexes.offset < (m_rowCount - 1_st))
            {
                ++m_indexes.offset;
            }
            else
            {
                ++m_indexes.display;
            }

            redraw();
            return true;
        }

        bool selectPrev()
        {
            if (m_items.empty() || (0 == selectedIndex()))
            {
                return false;
            }

            if (m_indexes.offset > 0)
            {
                --m_indexes.offset;
            }
            else
            {
                --m_indexes.display;
            }

            redraw();
            return true;
        }

        void redraw()
        {
            if (m_items.empty())
            {
                m_indexes.offset  = 0;
                m_indexes.display = 0;
            }

            while (!m_items.empty() && (selectedIndex() >= m_items.size()))
            {
                selectPrev();
            }

            m_bgRectangle.setFillColor(sf::Color(80, 80, 80, 80));
            m_bgRectangle.setOutlineColor(sf::Color(150, 150, 150, 127));

            if (m_hasFocus)
            {
                m_bgRectangle.setFillColor(m_bgRectangle.getFillColor() + m_highlightColor);
                m_bgRectangle.setOutlineColor(m_bgRectangle.getOutlineColor() + m_highlightColor);
            }

            m_rowLineVerts.clear();
            for (const sf::FloatRect & rect : m_rowRects)
            {
                util::appendLineVerts(rect, m_rowLineVerts, sf::Color(100, 100, 100, 127));
            }

            for (std::size_t offset = 0; offset < m_rowTexts.size(); ++offset)
            {
                std::string rowString;

                const std::size_t itemIndex{ m_indexes.display + offset };
                if (itemIndex < m_items.size())
                {
                    rowString = toString(m_items[itemIndex]);
                }

                m_rowTexts[offset].setString(rowString);
            }

            m_selectionRectangle.setPosition(util::position(m_rowRects[m_indexes.offset]));

            float fillRatio = 0.0f;
            if (m_items.size() >= m_rowCount)
            {
                fillRatio = (static_cast<float>(m_rowCount) / static_cast<float>(m_items.size()));
            }

            m_guideRectangle.setSize(
                { 1.0f, (fillRatio * m_bgRectangle.getGlobalBounds().height) });

            float scrollRatio = 0.0f;
            if ((m_items.size() > m_rowCount) && (m_items.size() > m_indexes.display))
            {
                scrollRatio =
                    (static_cast<float>(m_indexes.display) /
                     static_cast<float>(m_items.size() - m_rowCount));
            }

            const float guideVertPos =
                (m_bgRectangle.getGlobalBounds().top +
                 (scrollRatio * (m_bgRectangle.getGlobalBounds().height -
                                 m_guideRectangle.getGlobalBounds().height)));

            m_guideRectangle.setPosition(
                (m_bgRectangle.getGlobalBounds().left - 3.0f), guideVertPos);
        }

      private:
        const std::vector<T> & m_items;
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

#endif // CASTLECRAWL_GUI_LISTBOX_HPP_INCLUDED
