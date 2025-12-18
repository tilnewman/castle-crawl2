// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// experience-bar.cpp
//
#include "experience-bar.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "player.hpp"

namespace castlecrawl
{

    ExperienceBar::ExperienceBar()
        : m_statBar{}
    {}

    void ExperienceBar::setup(const Context & t_context)
    {
        const sf::FloatRect topRect{ t_context.layout.topRegion() };

        sf::FloatRect rect;
        rect.size.y     = (topRect.size.y * t_context.config.stat_bar_height_ratio);
        rect.position.y = ((topRect.size.y - rect.size.y) - 3.0f);
        rect.size.x     = (topRect.size.x * 0.275f);
        rect.position.x = ((topRect.size.x - rect.size.x) - 5.0f);

        m_statBar.setup(
            t_context,
            rect,
            sf::Color(160, 160, 190),
            t_context.player.experienceOffset(),
            t_context.player.experienceForLevel(t_context.player.level() + 1) -
                t_context.player.experienceForLevel(t_context.player.level()));
    }

    void ExperienceBar::update(const Context & t_context)
    {
        m_statBar.setMaxValue(t_context, t_context.player.experienceForNextLevel());
        m_statBar.setCurrentValue(t_context, t_context.player.experienceOffset());
    }

    void ExperienceBar::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_statBar, t_states);
    }

} // namespace castlecrawl
