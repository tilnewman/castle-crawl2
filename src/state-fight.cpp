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
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "state-treasure.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StateFight::StateFight()
        : m_isDirectionSelected{ false }
        , m_directionSelectDisplay{}
    {}

    void StateFight::onEnter(const Context & t_context)
    {
        m_directionSelectDisplay.setup(t_context);
    }

    void StateFight::update(const Context & t_context, const float)
    {
        t_context.framerate.update();
    }

    void StateFight::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.enemies.draw(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.framerate.draw(t_target, t_states);
        t_target.draw(t_context.top_panel, t_states);

        if (!m_isDirectionSelected)
        {
            t_target.draw(m_directionSelectDisplay, t_states);
        }
    }

    void StateFight::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        // all other handlers are key released events
        if (t_event.type != sf::Event::KeyPressed)
        {
            return;
        }

        if (t_event.key.code == sf::Keyboard::Escape)
        {
            t_context.state.change(t_context, State::Play);
            return;
        }

        if (!m_isDirectionSelected &&
            ((t_event.key.code == sf::Keyboard::Up) || (t_event.key.code == sf::Keyboard::Down) ||
             (t_event.key.code == sf::Keyboard::Left) || (t_event.key.code == sf::Keyboard::Right)))
        {
            handleSelectDirection(t_context, t_event.key.code);
            return;
        }
    }

    void StateFight::handleSelectDirection(const Context & t_context, const sf::Keyboard::Key t_key)
    {
        const MapPos_t mapPos = t_context.player_display.position();

        const MapPos_t upPos{ mapPos.x, (mapPos.y - 1) };
        const MapPos_t downPos{ mapPos.x, (mapPos.y + 1) };
        const MapPos_t leftPos{ (mapPos.x - 1), mapPos.y };
        const MapPos_t rightPos{ (mapPos.x + 1), mapPos.y };

        if ((t_key == sf::Keyboard::Up) && (t_context.maps.current().isPosValid(upPos)))
        {
            m_isDirectionSelected = true;
            fight(t_context, upPos);
        }
        else if ((t_key == sf::Keyboard::Down) && (t_context.maps.current().isPosValid(downPos)))
        {
            m_isDirectionSelected = true;
            fight(t_context, downPos);
        }
        else if ((t_key == sf::Keyboard::Left) && (t_context.maps.current().isPosValid(leftPos)))
        {
            m_isDirectionSelected = true;
            fight(t_context, leftPos);
        }
        else if ((t_key == sf::Keyboard::Right) && (t_context.maps.current().isPosValid(rightPos)))
        {
            m_isDirectionSelected = true;
            fight(t_context, rightPos);
        }
        else
        {
            t_context.sfx.play("error-1.ogg");
        }
    }

    void StateFight::fight(const Context & t_context, const MapPos_t & t_pos)
    {
        const char objectChar = t_context.maps.current().cell(t_pos).object_char;

        // TODO lots more needed here, like checking for enemies etc.
        if (objectChar == ' ')
        {
            t_context.sfx.play("miss.ogg");
            t_context.state.change(t_context, State::Play);
            return;
        }
        else if (objectChar == 'b')
        {
            t_context.sfx.play("barrel-break.ogg");

            t_context.maps.current().setObjectChar(t_pos, ' ');
            t_context.map_display.load(t_context);

            const item::Treasure treasure = t_context.items.randomTreasureFind(t_context);
            if (treasure.empty())
            {
                t_context.state.change(t_context, State::Play);
            }
            else
            {
                StateTreasure::setTreasure(treasure);
                t_context.state.change(t_context, State::Treasure);
            }

            return;
        }
        else
        {
            t_context.sfx.play("hit.ogg");
            t_context.state.change(t_context, State::Play);
            return;
        }
    }

} // namespace castlecrawl
