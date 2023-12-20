// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-fight.cpp
//
#include "state-fight.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "enemy.hpp"
#include "framerate-text.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "map.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StateFight::StateFight()
        : m_isDirectionSelected(false)
        , m_directionSelectDisplay()
    {}

    void StateFight::onEnter(const Context & context) { m_directionSelectDisplay.setup(context); }

    void StateFight::update(const Context & context, const float) { context.framerate.update(); }

    void StateFight::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.clear(context.config.background_color);
        context.map_display.draw(context, target, states);
        context.enemies.draw(context, target, states);
        context.player_display.draw(context, target, states);
        context.framerate.draw(target, states);
        target.draw(context.top_panel, states);

        if (!m_isDirectionSelected)
        {
            target.draw(m_directionSelectDisplay, states);
        }
    }

    void StateFight::handleEvent(const Context & context, const sf::Event & event)
    {
        // all other handlers are key released events
        if (event.type != sf::Event::KeyReleased)
        {
            return;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            context.state.change(context, State::Play);
            return;
        }

        if (!m_isDirectionSelected &&
            ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down) ||
             (event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::Right)))
        {
            handleSelectDirection(context, event.key.code);
            return;
        }
    }

    void StateFight::handleSelectDirection(const Context & context, const sf::Keyboard::Key key)
    {
        const MapPos_t mapPos = context.player_display.position();

        const MapPos_t upPos{ mapPos.x, (mapPos.y - 1) };
        const MapPos_t downPos{ mapPos.x, (mapPos.y + 1) };
        const MapPos_t leftPos{ (mapPos.x - 1), mapPos.y };
        const MapPos_t rightPos{ (mapPos.x + 1), mapPos.y };

        if ((key == sf::Keyboard::Up) && (context.map.isPosValid(upPos)))
        {
            m_isDirectionSelected = true;
            fight(context, upPos);
        }
        else if ((key == sf::Keyboard::Down) && (context.map.isPosValid(downPos)))
        {
            m_isDirectionSelected = true;
            fight(context, downPos);
        }
        else if ((key == sf::Keyboard::Left) && (context.map.isPosValid(leftPos)))
        {
            m_isDirectionSelected = true;
            fight(context, leftPos);
        }
        else if ((key == sf::Keyboard::Right) && (context.map.isPosValid(rightPos)))
        {
            m_isDirectionSelected = true;
            fight(context, rightPos);
        }
        else
        {
            context.sfx.play("error-1.ogg");
        }
    }

    void StateFight::fight(const Context & context, const MapPos_t & pos)
    {
        const char objectChar = context.map.cell(pos).object_char;

        if (objectChar == ' ')
        {
            context.sfx.play("miss.ogg");
        }
        else if (objectChar == 'b')
        {
            context.sfx.play("barrel-break.ogg");
        }
        else
        {
            context.sfx.play("hit.ogg");
        }

        context.state.change(context, State::Play);
    }

} // namespace castlecrawl
