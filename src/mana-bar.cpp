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
        rect.height = (topRect.height * 0.1f);
        rect.top    = ((topRect.height - rect.height) - 3.0f);
        rect.width  = (topRect.width * 0.25f);
        rect.left   = ((topRect.width * 0.5f) - (rect.width * 0.5f));

        rect.top -= rect.height;
        rect.top -= 5.0f;

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
