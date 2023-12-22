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
        : m_statBar()
    {}

    void HealthBar::setup(const Context & context)
    {
        const sf::FloatRect topRect = context.layout.topRect();

        sf::FloatRect healthBarRect;
        healthBarRect.height = (topRect.height * 0.1f);
        healthBarRect.top    = ((topRect.height - healthBarRect.height) - 3.0f);
        healthBarRect.width  = (topRect.width * 0.25f);
        healthBarRect.left   = ((topRect.width * 0.5f) - (healthBarRect.width * 0.5f));

        m_statBar.setup(
            context, healthBarRect, sf::Color(160, 0, 0), context.player.health().max());
    }

    void HealthBar::update(const Context & context)
    {
        m_statBar.setMaxValue(context, context.player.health().max());
        m_statBar.setCurrentValue(context, context.player.health().current());
    }

    void HealthBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_statBar, states);
    }

} // namespace castlecrawl
