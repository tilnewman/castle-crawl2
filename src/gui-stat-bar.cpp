// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// gui-stat-bar.cpp
//
#include "gui-stat-bar.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "util.hpp"

#include <string>

namespace castlecrawl
{

    StatBar::StatBar()
        : m_text()
        , m_color()
        , m_max(0)
        , m_current(0)
        , m_outerRectangle()
        , m_innerRectangle()
    {}

    void StatBar::setup(
        const Context & context,
        const sf::FloatRect & region,
        const sf::Color & color,
        const int maxValue)
    {
        m_max = maxValue;

        m_outerRectangle.setFillColor(sf::Color::Transparent);
        m_outerRectangle.setOutlineThickness(2.0f);
        m_outerRectangle.setOutlineColor(color);
        m_outerRectangle.setSize(util::size(region));
        m_outerRectangle.setPosition(util::position(region));

        m_innerRectangle.setFillColor(color - sf::Color(60, 60, 60, 0));
        m_innerRectangle.setOutlineColor(sf::Color::Transparent);
        m_innerRectangle.setOutlineThickness(0.0f);
        m_innerRectangle.setPosition(util::position(region) + sf::Vector2f{ 1.0f, 1.0f });
        m_innerRectangle.setSize(util::size(region) - sf::Vector2f{ 2.0f, 2.0f });

        m_color = color;
        setCurrentValue(context, maxValue);
    }

    void StatBar::setCurrentValue(const Context & context, const int newValue)
    {
        m_current = newValue;
        update(context);
    }

    void StatBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_outerRectangle, states);
        target.draw(m_innerRectangle, states);
        target.draw(m_text, states);
    }

    void StatBar::update(const Context & context)
    {
        std::string str;
        str += std::to_string(m_current);
        str += " / ";
        str += std::to_string(m_max);

        m_text =
            context.fonts.makeText(FontSize::Small, str, (m_color + sf::Color(100, 100, 100, 0)));

        util::fitAndCenterInside(m_text, m_innerRectangle.getGlobalBounds());
    }

} // namespace castlecrawl
