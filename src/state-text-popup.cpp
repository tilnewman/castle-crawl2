// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-text-popup.cpp
//
#include "state-text-popup.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "monster-manager.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"
#include "turn-keeper.hpp"

namespace castlecrawl
{

    StateTextPopup::StateTextPopup()
        : m_backgroundRectangle{}
        , m_textLayout{}
    {}

    void StateTextPopup::onEnter(const Context & t_context)
    {
        sf::FloatRect rect = t_context.layout.screenRegion();
        util::scaleRectInPlace(rect, 0.35f);

        m_textLayout = TextLayout::typeset(
            t_context,
            m_info.message,
            rect,
            m_info.font_size,
            0.1f,
            m_info.will_center_justify,
            m_info.color);

        m_backgroundRectangle.setPosition(m_textLayout.rect_outer.position);
        m_backgroundRectangle.setSize(m_textLayout.rect_outer.size);
        m_backgroundRectangle.setFillColor(sf::Color::Black);
        m_backgroundRectangle.setOutlineThickness(2.0f);
        m_backgroundRectangle.setOutlineColor(sf::Color::White);
    }

    void StateTextPopup::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateTextPopup::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.draw(t_context, t_target, t_states);
        t_context.npcs.draw(t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);
        t_context.framerate.draw(t_target, t_states);

        t_target.draw(t_context.top_panel, t_states);
        t_target.draw(m_backgroundRectangle, t_states);

        for (const sf::Text & text : m_textLayout.texts)
        {
            t_target.draw(text, t_states);
        }
    }

    void StateTextPopup::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>();
        if (keyPtr)
        {
            if (m_info.will_advance_turn)
            {
                t_context.turn.advance(t_context, t_context.config.turn_delay_after_player_misc);
            }

            t_context.state.setChangePending(State::Play);
        }
    }

} // namespace castlecrawl
