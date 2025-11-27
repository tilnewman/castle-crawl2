// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-death.cpp
//
#include "state-death.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "monster-manager.hpp"
#include "music-player.hpp"
#include "player-display.hpp"
#include "sfml-defaults.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{
    StateDeath::StateDeath()
        : m_fadeRedRectangle{}
        , m_fadeBlackRectangle{}
        , m_titleText{ util::SfmlDefaults::instance().font() }
        , m_fadeRedTimeSec{ 0.0f }
        , m_fadeBlackTimeSec{ 0.0f }
    {}

    void StateDeath::onEnter(const Context & t_context)
    {
        t_context.music.stopAll();
        t_context.sfx.play("game-over.ogg");

        const sf::FloatRect screenRect{ t_context.layout.screenRegion() };

        m_fadeRedRectangle.setFillColor(sf::Color(255, 0, 0, 0));
        m_fadeRedRectangle.setSize(screenRect.size);

        m_fadeBlackRectangle.setFillColor(sf::Color(0, 0, 0, 0));
        m_fadeBlackRectangle.setSize(screenRect.size);

        m_titleText = t_context.fonts.makeText(FontSize::Huge, "You Died", sf::Color::Red);
        util::centerInside(m_titleText, screenRect);
    }

    void StateDeath::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.anim.update(t_context, t_elapsedSec);

        if (m_fadeRedRectangle.getFillColor().a < 255)
        {
            m_fadeRedTimeSec += t_elapsedSec;
            if (m_fadeRedTimeSec > 0.035f)
            {
                m_fadeRedTimeSec = 0.0f;
                sf::Color color  = m_fadeRedRectangle.getFillColor();
                ++color.a;
                m_fadeRedRectangle.setFillColor(color);

                color = m_titleText.getFillColor();
                color -= sf::Color(1, 1, 1, 0);
                m_titleText.setFillColor(color);
            }
        }
        else if (m_fadeBlackRectangle.getFillColor().a < 255)
        {
            m_fadeBlackTimeSec += t_elapsedSec;
            if (m_fadeBlackTimeSec > 0.005f)
            {
                m_fadeBlackTimeSec = 0.0f;
                sf::Color color    = m_fadeBlackRectangle.getFillColor();
                ++color.a;
                m_fadeBlackRectangle.setFillColor(color);
            }
        }
        else
        {
            t_context.state.setChangePending(State::Credits);
        }
    }

    void StateDeath::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.drawHealthLines(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);

        t_target.draw(t_context.top_panel, t_states);
        t_target.draw(m_fadeRedRectangle, t_states);
        t_target.draw(m_fadeBlackRectangle, t_states);

        if (m_fadeRedRectangle.getFillColor().a < 255)
        {
            t_target.draw(m_titleText, t_states);
        }
    }

    void StateDeath::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                t_context.state.setChangePending(State::Credits);
            }
        }
    }

} // namespace castlecrawl
