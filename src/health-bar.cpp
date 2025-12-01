// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// health-bar.cpp
//
#include "health-bar.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "player.hpp"

namespace castlecrawl
{

    HealthBar::HealthBar()
        : m_statBar{}
    {}

    void HealthBar::setup(const Context & t_context)
    {
        const sf::FloatRect topRect{ t_context.layout.topRegion() };

        sf::FloatRect healthBarRect;
        healthBarRect.size.y     = (topRect.size.y * 0.1f);
        healthBarRect.position.y = ((topRect.size.y - healthBarRect.size.y) - 3.0f);
        healthBarRect.size.x     = (topRect.size.x * 0.275f);
        healthBarRect.position.x = ((topRect.size.x * 0.5f) - (healthBarRect.size.x * 0.5f));

        m_statBar.setup(
            t_context,
            healthBarRect,
            sf::Color(180, 20, 20),
            t_context.player.health(),
            t_context.player.healthMax());
    }

    void HealthBar::update(const Context & t_context)
    {
        m_statBar.setMaxValue(t_context, t_context.player.healthMax());
        m_statBar.setCurrentValue(t_context, t_context.player.health());
    }

    void HealthBar::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_statBar, t_states);
    }

} // namespace castlecrawl
