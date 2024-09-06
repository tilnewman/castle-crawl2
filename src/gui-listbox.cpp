// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// gui-listbox.cpp
//
#include "gui-listbox.hpp"

namespace castlecrawl
{

    Listbox::Listbox(const std::vector<item::Item> & t_items)
        : m_items{ t_items }
        , m_hasFocus{}
        , m_rowCount{ 0 }
        , m_highlightColor{ 20, 20, 20, 20 }
        , m_bgRectangle{}
        , m_indexes{}
        , m_rowRects{}
        , m_rowLineVerts{}
        , m_rowTexts{}
        , m_selectionRectangle{}
        , m_guideRectangle{}
    {}

    void Listbox::setup(
        const Context & t_context,
        const FontSize t_fontSize,
        const std::size_t t_widthCharsMax,
        const std::size_t t_heightRows)
    {
        m_rowCount = t_heightRows;

        const sf::Vector2f letterSize = t_context.fonts.extent(t_fontSize).letter_size;

        m_bgRectangle.setSize({ (letterSize.x * static_cast<float>(t_widthCharsMax)),
                                (letterSize.y * static_cast<float>(t_heightRows)) });

        m_bgRectangle.setOutlineThickness(1.0f);

        m_rowRects.clear();
        float posTop = m_bgRectangle.getGlobalBounds().top;
        for (std::size_t i = 0; i < t_heightRows; ++i)
        {
            sf::FloatRect rect{ m_bgRectangle.getGlobalBounds() };

            rect.height =
                (m_bgRectangle.getGlobalBounds().height / static_cast<float>(t_heightRows));

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
            sf::Text & text = m_rowTexts.emplace_back(t_context.fonts.makeText(t_fontSize, "Tyjp"));

            // use this only to vertically center
            util::centerInside(text, m_rowRects[i]);

            text.setPosition((util::position(m_rowRects[i]).x + 1.0f), text.getGlobalBounds().top);
        }

        m_selectionRectangle.setFillColor(sf::Color(255, 255, 255, 40));
        m_selectionRectangle.setSize(util::size(m_rowRects[0]));

        m_guideRectangle.setFillColor(sf::Color(255, 255, 255, 127));

        redraw();
    }

    void Listbox::setPosition(const sf::Vector2f & t_pos)
    {
        const sf::Vector2f move{ t_pos - util::position(m_bgRectangle) };
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

    void Listbox::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(&m_rowLineVerts[0], m_rowLineVerts.size(), sf::PrimitiveType::Lines);
        t_target.draw(m_bgRectangle, t_states);

        if (m_hasFocus && !m_items.empty())
        {
            t_target.draw(m_selectionRectangle, t_states);
        }

        for (const sf::Text & text : m_rowTexts)
        {
            t_target.draw(text, t_states);
        }

        if (!empty())
        {
            t_target.draw(m_guideRectangle, t_states);
        }
    }

    bool Listbox::selectNext()
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

    bool Listbox::selectPrev()
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

    void Listbox::redraw()
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
                const item::Item & item = m_items[itemIndex];
                rowString               = toString(item);

                if (item.isArmor())
                {
                    m_rowTexts[offset].setFillColor(sf::Color(255, 220, 200));
                }
                else if (item.isWeapon())
                {
                    m_rowTexts[offset].setFillColor(sf::Color(200, 200, 255));
                }
                else
                {
                    m_rowTexts[offset].setFillColor(sf::Color(200, 255, 200));
                }
            }

            m_rowTexts[offset].setString(rowString);
        }

        m_selectionRectangle.setPosition(util::position(m_rowRects[m_indexes.offset]));

        float fillRatio = 0.0f;
        if (m_items.size() >= m_rowCount)
        {
            fillRatio = (static_cast<float>(m_rowCount) / static_cast<float>(m_items.size()));
        }

        m_guideRectangle.setSize({ 1.0f, (fillRatio * m_bgRectangle.getGlobalBounds().height) });

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

        m_guideRectangle.setPosition((m_bgRectangle.getGlobalBounds().left - 3.0f), guideVertPos);
    }

} // namespace castlecrawl
