// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-play.cpp
//
#include "state-play.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "dust-particle.hpp"
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

    void StatePlay::update(const Context & t_context, const float t_frameTimeSec)
    {
        t_context.enemies.update(t_context, t_frameTimeSec);
        m_mouseover.update(t_context, t_frameTimeSec);
        t_context.player_display.update(t_context, t_frameTimeSec);
        t_context.framerate.update();
        t_context.dust_particles.update(t_context, t_frameTimeSec);
    }

    void StatePlay::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.enemies.draw(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.dust_particles.draw(t_target, t_states);
        m_mouseover.draw(t_context, t_target, t_states);
        t_context.framerate.draw(t_target, t_states);
        t_target.draw(t_context.top_panel, t_states);
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

    void StatePlay::handlePlayerMove(const Context & t_context, const sf::Keyboard::Scancode t_key)
    {
        const MapPos_t mapPosBefore    = t_context.player_display.position();
        const MapPos_t mapPosAttempted = util::keys::moveIfDir(mapPosBefore, t_key);
        const bool isEnemyInTheWay     = t_context.enemies.isAnyAtMapPos(mapPosAttempted);
        const char mapCharAttempted    = t_context.maps.current().cell(mapPosAttempted).object_char;

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

        playMoveSfx(t_context, didMove, mapCharAttempted);

        // handle walking into lava or slime health drop
        if (!didMove && ((mapCharAttempted == 'l') || (mapCharAttempted == 'g')))
        {
            t_context.player_display.shake();
            t_context.player_display.bloodSplatStart(t_context);

            t_context.player.health().adjCurrent(-1);
            t_context.top_panel.update(t_context);

            if (t_context.player.health().current() == 0)
            {
                t_context.player_display.bloodSplatStop();
                t_context.state.change(t_context, State::Death);
            }

            return;
        }

        if (didMove)
        {
            t_context.player_display.position(t_context, mapPosAfter);
            handleMapTransition(t_context, mapPosAfter);
            playMoveMusic(t_context);
        }
    }

    void StatePlay::playMoveSfx(
        const Context & t_context, const bool t_didMove, const char t_mapCharAttempted) const
    {
        if (t_didMove)
        {
            if (t_mapCharAttempted == 'd')
            {
                t_context.sfx.play("door-open");
            }
            else if ((t_mapCharAttempted == 's') || (t_mapCharAttempted == 'S'))
            {
                t_context.sfx.play("stairs");
            }
            else
            {
                t_context.sfx.play("tick-off-1");
            }
        }
        else
        {
            if (t_mapCharAttempted == 'D')
            {
                t_context.sfx.play("locked");
            }
            else if (t_mapCharAttempted == 'w')
            {
                t_context.sfx.play("splash");
            }
            else if (t_mapCharAttempted == 'l')
            {
                t_context.sfx.play("burn");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
    }

    void StatePlay::playMoveMusic(const Context & t_context) const
    {
        const auto surroundingCells =
            t_context.maps.current().surroundingCellsAll(t_context.player_display.position());

        const auto foundLavaIter = std::find_if(
            std::begin(surroundingCells), std::end(surroundingCells), [](const MapCell & cell) {
                return (cell.object_char == 'l');
            });

        if (foundLavaIter == std::end(surroundingCells))
        {
            t_context.music.stop("lava.ogg");
        }
        else
        {
            t_context.music.start("lava.ogg");
        }

        const auto foundWaterIter = std::find_if(
            std::begin(surroundingCells), std::end(surroundingCells), [](const MapCell & cell) {
                return (cell.object_char == 'w');
            });

        if (foundWaterIter == std::end(surroundingCells))
        {
            t_context.music.stop("water-bubbles.ogg");
        }
        else
        {
            t_context.music.start("water-bubbles.ogg");
        }
    }

    bool StatePlay::handleMapTransition(const Context & t_context, const MapPos_t & t_mapPosAfter)
    {
        for (const MapTransition & transition : t_context.maps.current().transitions())
        {
            if (transition.from_pos == t_mapPosAfter)
            {
                t_context.maps.change(t_context, transition.to_name, transition.to_pos);
                m_mouseover.reset();
                return true;
            }
        }

        return false;
    }

} // namespace castlecrawl
