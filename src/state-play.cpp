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
        target.clear(context.config.background_color);
        context.map_display.draw(context, target, states);
        context.enemies.draw(context, target, states);
        context.player_display.draw(context, target, states);
        m_mouseover.draw(context, target, states);
        context.framerate.draw(target, states);
        context.top_panel.draw(context, target, states);
        target.draw(context.health_bar, states);
        target.draw(context.mana_bar, states);
    }

    void StatePlay::handleEvent(const Context & context, const sf::Event & event)
    {
        if (event.type == sf::Event::MouseMoved)
        {
            m_mouseover.handleMouseMovedEvent({ event.mouseMove.x, event.mouseMove.y });
            return;
        }

        // all other handlers are key released events
        if (event.type != sf::Event::KeyReleased)
        {
            return;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            context.state.change(context, State::Quit);
            return;
        }
        else if (
            (event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down) ||
            (event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::Right))
        {
            handlePlayerMove(context, event.key.code);
            return;
        }
        else if (event.key.code == sf::Keyboard::I)
        {
            context.state.change(context, State::Inventory);
            return;
        }
        else if (event.key.code == sf::Keyboard::F)
        {
            context.state.change(context, State::Fight);
            return;
        }
    }

    void StatePlay::handlePlayerMove(const Context & context, const sf::Keyboard::Key key)
    {
        const MapPos_t mapPosBefore    = context.player_display.position();
        const MapPos_t mapPosAttempted = keys::moveIfDir(mapPosBefore, key);
        const bool isEnemyInTheWay     = context.enemies.isAnyAtMapPos(mapPosAttempted);
        const char mapCharAttempted    = context.map.cell(mapPosAttempted).object_char;

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

        // handle walking into lava health drop
        if (!didMove && (mapCharAttempted == 'l'))
        {
            context.player_display.shake();
            context.player.health().adjCurrent(-1);
            context.health_bar.update(context);
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
            context.map.surroundingCellsAll(context.player_display.position());

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
        for (const MapTransition & transition : context.map.transitions())
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
