// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-look-event.cpp
//
#include "state-look-event.hpp"

#include "animation-manager.hpp"
#include "check-macros.hpp"
#include "context.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "look-event.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StateLookEvent::StateLookEvent()
        : m_backgroundRectangle{}
        , m_textLayout{}
    {}

    void StateLookEvent::onEnter(const Context & t_context)
    {
        M_CHECK(
            !m_lookEvent.empty(), "State LookEvent was switched to but there was no LookEvent!");

        sf::FloatRect rect = t_context.layout.screenRegion();
        util::scaleRectInPlace(rect, 0.5f);

        std::string message = m_lookEvent.message;
        if (m_lookEvent.hasRequirements())
        {
            message += ' ';

            if (LookEventHandler::areAllRequirementsMet(t_context, m_lookEvent))
            {
                message += m_lookEvent.message_pass;
                LookEventHandler::takePassActions(t_context, m_lookEvent);
                t_context.maps.current().setLookEventAsHappened(m_lookEvent.map_pos);
                t_context.sfx.play("magic-1");
            }
            else
            {
                message += m_lookEvent.message_fail;
                LookEventHandler::takeFailActions(t_context, m_lookEvent);
            }
        }
        else
        {
            t_context.maps.current().setLookEventAsHappened(m_lookEvent.map_pos);
        }

        m_textLayout = TextLayout::typeset(
            t_context,
            message,
            rect,
            FontSize::Medium,
            0.1f,
            true,
            t_context.config.message_color_popup);

        m_backgroundRectangle.setPosition(m_textLayout.rect_outer.position);
        m_backgroundRectangle.setSize(m_textLayout.rect_outer.size);
        m_backgroundRectangle.setFillColor(t_context.config.message_color_popup_bg);
        m_backgroundRectangle.setOutlineThickness(2.0f);
        m_backgroundRectangle.setOutlineColor(sf::Color::White);
    }

    void StateLookEvent::onExit(const Context &) { m_lookEvent = LookEvent(); }

    void StateLookEvent::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateLookEvent::draw(
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

    void StateLookEvent::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if ((keyPtr->scancode == sf::Keyboard::Scancode::Escape) ||
                (keyPtr->scancode == sf::Keyboard::Scancode::Enter))
            {
                t_context.state.setChangePending(State::Play);
            }
        }
    }

} // namespace castlecrawl
