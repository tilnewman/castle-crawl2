// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// mana-bar.cpp
//
#include "mana-bar.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "player.hpp"

namespace castlecrawl
{

    ManaBar::ManaBar()
        : m_statBar()
    {}

    void ManaBar::setup(const Context & t_context)
    {
        const sf::FloatRect topRect = t_context.layout.topRect();

        sf::FloatRect rect;
        rect.size.y     = (topRect.size.y * 0.1f);
        rect.position.y = ((topRect.size.y - rect.size.y) - 3.0f);
        rect.size.x     = (topRect.size.x * 0.25f);
        rect.position.x = ((topRect.size.x * 0.5f) - (rect.size.x * 0.5f));

        rect.position.y -= rect.size.y;
        rect.position.y -= 5.0f;

        m_statBar.setup(t_context, rect, sf::Color(100, 0, 220), t_context.player.mana().max());
    }

    void ManaBar::update(const Context & t_context)
    {
        m_statBar.setMaxValue(t_context, t_context.player.mana().max());
        m_statBar.setCurrentValue(t_context, t_context.player.mana().current());
    }

    void ManaBar::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_statBar, t_states);
    }

} // namespace castlecrawl
