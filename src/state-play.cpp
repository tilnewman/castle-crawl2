// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-play.cpp
//
#include "state-play.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "enemy.hpp"
#include "framerate-text.hpp"
#include "health-bar.hpp"
#include "keys.hpp"
#include "layout.hpp"
#include "mana-bar.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "mouseover.hpp"
#include "music-player.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StatePlay::StatePlay()
        : m_mouseover()
    {}

    void StatePlay::onEnter(const Context &) {}

    void StatePlay::update(const Context & context, const float frameTimeSec)
    {
        context.enemies.update(context, frameTimeSec);
        m_mouseover.update(context, frameTimeSec);
        context.player_display.update(context, frameTimeSec);
        context.framerate.update();
    }

    void StatePlay::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        context.map_display.draw(context, target, states);
        context.enemies.draw(context, target, states);
        context.player_display.draw(context, target, states);
        m_mouseover.draw(context, target, states);
        context.framerate.draw(target, states);
        target.draw(context.top_panel, states);
    }

    void StatePlay::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * movePtr = t_event.getIf<sf::Event::MouseMoved>())
        {
            m_mouseover.handleMouseMovedEvent(movePtr->position);
            return;
        }

        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                t_context.state.change(t_context, State::Quit);
            }
            else if (
                (keyPtr->scancode == sf::Keyboard::Scancode::Up) ||
                (keyPtr->scancode == sf::Keyboard::Scancode::Down) ||
                (keyPtr->scancode == sf::Keyboard::Scancode::Left) ||
                (keyPtr->scancode == sf::Keyboard::Scancode::Right))
            {
                handlePlayerMove(t_context, keyPtr->scancode);
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::I)
            {
                t_context.state.change(t_context, State::Inventory);
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::F)
            {
                t_context.state.change(t_context, State::Fight);
            }
        }
    }

    void StatePlay::handlePlayerMove(const Context & context, const sf::Keyboard::Scancode key)
    {
        const MapPos_t mapPosBefore    = context.player_display.position();
        const MapPos_t mapPosAttempted = util::keys::moveIfDir(mapPosBefore, key);
        const bool isEnemyInTheWay     = context.enemies.isAnyAtMapPos(mapPosAttempted);
        const char mapCharAttempted    = context.maps.current().cell(mapPosAttempted).object_char;

        const MapPos_t mapPosAfter = [&]() {
            if (isEnemyInTheWay)
            {
                return mapPosBefore;
            }
            else if (
                (mapCharAttempted == ' ') || (mapCharAttempted == 'd') ||
                (mapCharAttempted == '.') || (mapCharAttempted == 's') || (mapCharAttempted == 'S'))
            {
                return mapPosAttempted;
            }
            else
            {
                return mapPosBefore;
            }
        }();

        const bool didMove = (mapPosBefore != mapPosAfter);

        playMoveSfx(context, didMove, mapCharAttempted);

        // handle walking into lava or slime health drop
        if (!didMove && ((mapCharAttempted == 'l') || (mapCharAttempted == 'g')))
        {
            context.player_display.shake();

            context.player.health().adjCurrent(-1);
            context.top_panel.update(context);

            if (context.player.health().current() == 0)
            {
                context.state.change(context, State::Death);
            }

            return;
        }

        if (didMove)
        {
            context.player_display.position(context, mapPosAfter);
            handleMapTransition(context, mapPosAfter);
            playMoveMusic(context);
        }
    }

    void StatePlay::playMoveSfx(
        const Context & context, const bool didMove, const char mapCharAttempted) const
    {
        if (didMove)
        {
            if (mapCharAttempted == 'd')
            {
                context.sfx.play("door-open");
            }
            else if ((mapCharAttempted == 's') || (mapCharAttempted == 'S'))
            {
                context.sfx.play("stairs");
            }
            else
            {
                context.sfx.play("tick-off-1");
            }
        }
        else
        {
            if (mapCharAttempted == 'D')
            {
                context.sfx.play("locked");
            }
            else if (mapCharAttempted == 'w')
            {
                context.sfx.play("splash");
            }
            else if (mapCharAttempted == 'l')
            {
                context.sfx.play("burn");
            }
            else
            {
                context.sfx.play("tap-wood-low");
            }
        }
    }

    void StatePlay::playMoveMusic(const Context & context) const
    {
        const auto surroundingCells =
            context.maps.current().surroundingCellsAll(context.player_display.position());

        const auto foundLavaIter = std::find_if(
            std::begin(surroundingCells), std::end(surroundingCells), [](const MapCell & cell) {
                return (cell.object_char == 'l');
            });

        if (foundLavaIter == std::end(surroundingCells))
        {
            context.music.stop("lava.ogg");
        }
        else
        {
            context.music.start("lava.ogg");
        }

        const auto foundWaterIter = std::find_if(
            std::begin(surroundingCells), std::end(surroundingCells), [](const MapCell & cell) {
                return (cell.object_char == 'w');
            });

        if (foundWaterIter == std::end(surroundingCells))
        {
            context.music.stop("water-bubbles.ogg");
        }
        else
        {
            context.music.start("water-bubbles.ogg");
        }
    }

    bool StatePlay::handleMapTransition(const Context & context, const MapPos_t & mapPosAfter)
    {
        for (const MapTransition & transition : context.maps.current().transitions())
        {
            if (transition.from_pos == mapPosAfter)
            {
                context.maps.change(context, transition.to_name, transition.to_pos);
                m_mouseover.reset();
                return true;
            }
        }

        return false;
    }

} // namespace castlecrawl
