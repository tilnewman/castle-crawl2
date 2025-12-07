// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-look.cpp
//
#include "state-look.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "framerate-text.hpp"
#include "look-event.hpp"
#include "look.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StateLook::StateLook()
        : m_isDirectionSelected{ false }
        , m_directionSelectDisplay{}
    {}

    void StateLook::onEnter(const Context & t_context)
    {
        m_directionSelectDisplay.setup(t_context);
    }

    void StateLook::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
        m_directionSelectDisplay.update(t_context, t_elapsedSec);
    }

    void StateLook::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.draw(t_context, t_target, t_states);
        t_context.npcs.draw(t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);
        t_context.framerate.draw(t_target, t_states);

        t_target.draw(t_context.top_panel, t_states);

        if (!m_isDirectionSelected)
        {
            t_target.draw(m_directionSelectDisplay, t_states);
        }
    }

    void StateLook::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                t_context.state.setChangePending(State::Play);
            }
            else if (
                !m_isDirectionSelected && ((keyPtr->scancode == sf::Keyboard::Scancode::Up) ||
                                           (keyPtr->scancode == sf::Keyboard::Scancode::Down) ||
                                           (keyPtr->scancode == sf::Keyboard::Scancode::Left) ||
                                           (keyPtr->scancode == sf::Keyboard::Scancode::Right)))
            {
                handleSelectDirection(t_context, keyPtr->scancode);
            }
        }
    }

    void StateLook::handleSelectDirection(
        const Context & t_context, const sf::Keyboard::Scancode t_key)
    {
        const MapPos_t mapPos{ t_context.player_display.position() };
        const MapPos_t upPos{ mapPos.x, (mapPos.y - 1) };
        const MapPos_t downPos{ mapPos.x, (mapPos.y + 1) };
        const MapPos_t leftPos{ (mapPos.x - 1), mapPos.y };
        const MapPos_t rightPos{ (mapPos.x + 1), mapPos.y };

        const LookEvent lookEvent = t_context.maps.current().lookEvent();

        if ((t_key == sf::Keyboard::Scancode::Up) && (t_context.maps.current().isPosValid(upPos)))
        {
            m_isDirectionSelected = true;
            t_context.look.look(t_context, upPos, true);
        }
        else if (
            (t_key == sf::Keyboard::Scancode::Down) &&
            (t_context.maps.current().isPosValid(downPos)))
        {
            m_isDirectionSelected = true;
            t_context.look.look(t_context, downPos, true);
        }
        else if (
            (t_key == sf::Keyboard::Scancode::Left) &&
            (t_context.maps.current().isPosValid(leftPos)))
        {
            m_isDirectionSelected = true;
            t_context.look.look(t_context, leftPos, true);
        }
        else if (
            (t_key == sf::Keyboard::Scancode::Right) &&
            (t_context.maps.current().isPosValid(rightPos)))
        {
            m_isDirectionSelected = true;
            t_context.look.look(t_context, rightPos, true);
        }
        else
        {
            t_context.sfx.play("error-1");
        }
    }

} // namespace castlecrawl
