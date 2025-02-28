// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// gui-stat-bar.cpp
//
#include "gui-stat-bar.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"

#include <string>

namespace castlecrawl
{

    StatBar::StatBar()
        : m_text(util::SfmlDefaults::instance().font())
        , m_color()
        , m_max(0)
        , m_current(0)
        , m_outerRectangle()
        , m_innerRectangle()
    {}

    void StatBar::setup(
        const Context & t_context,
        const sf::FloatRect & t_region,
        const sf::Color & t_color,
        const int t_maxValue)
    {
        m_max = t_maxValue;

        m_outerRectangle.setFillColor(sf::Color::Transparent);
        m_outerRectangle.setOutlineThickness(2.0f);
        m_outerRectangle.setOutlineColor(t_color);
        m_outerRectangle.setSize(t_region.size);
        m_outerRectangle.setPosition(t_region.position);

        m_innerRectangle.setFillColor(t_color - sf::Color(60, 60, 60, 0));
        m_innerRectangle.setOutlineColor(sf::Color::Transparent);
        m_innerRectangle.setOutlineThickness(0.0f);
        m_innerRectangle.setPosition(t_region.position + sf::Vector2f{ 1.0f, 1.0f });
        m_innerRectangle.setSize(t_region.size - sf::Vector2f{ 2.0f, 2.0f });

        m_color = t_color;
        setCurrentValue(t_context, t_maxValue);
    }

    void StatBar::setCurrentValue(const Context & t_context, const int t_newValue)
    {
        m_current = std::clamp(t_newValue, 0, m_max);
        update(t_context);
    }

    void StatBar::setMaxValue(const Context & t_context, const int t_newValue)
    {
        m_max = t_newValue;

        if (m_current > m_max)
        {
            m_current = m_max;
        }

        update(t_context);
    }

    void StatBar::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_outerRectangle, t_states);
        t_target.draw(m_innerRectangle, t_states);
        t_target.draw(m_text, t_states);
    }

    void StatBar::update(const Context & t_context)
    {
        std::string str;
        str += std::to_string(m_current);
        str += " / ";
        str += std::to_string(m_max);

        m_text =
            t_context.fonts.makeText(FontSize::Small, str, (m_color + sf::Color(100, 100, 100, 0)));

        util::fitAndCenterInside(m_text, m_innerRectangle.getGlobalBounds());

        const float maxWidth{ m_outerRectangle.getSize().x - 2.0f };
        const float ratio{ static_cast<float>(m_current) / static_cast<float>(m_max) };
        m_innerRectangle.setSize({ (ratio * maxWidth), m_innerRectangle.getSize().y });
    }

} // namespace castlecrawl
