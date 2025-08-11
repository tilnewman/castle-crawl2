// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-manager.cpp
//
#include "monster-manager.hpp"

#include "context.hpp"
#include "fight-util.hpp"
#include "font.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"

#include <algorithm>

namespace castlecrawl
{

    MonsterManager::MonsterManager()
        : m_monsters{}
    {}

    void MonsterManager::add(
        const Context & t_context, const MapPos_t & t_mapPos, const char t_mapChar)
    {
        m_monsters.emplace_back(t_context, t_mapPos, charToTileImage(t_mapChar));
    }

    bool MonsterManager::takeTurns(const Context & t_context)
    {
        bool didAnyMonstersMove = false;
        for (Monster & monster : m_monsters)
        {
            if (!monster.isAlive())
            {
                continue;
            }

            if (monster.takeTurn(t_context))
            {
                didAnyMonstersMove = true;
            }
        }

        return didAnyMonstersMove;
    }

    void MonsterManager::drawHealthLines(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const Monster & monster : m_monsters)
        {
            if (monster.healthRatio() < 1.0f)
            {
                const auto rectangles{ makeCreatureHealthBars(
                    t_context, monster.healthRatio(), monster.mapPosition()) };

                t_target.draw(rectangles.background, t_states);
                t_target.draw(rectangles.foreground, t_states);
            }
        }
    }

    const MonsterStats MonsterManager::stats(const MapPos_t & t_mapPos) const
    {
        for (const Monster & monster : m_monsters)
        {
            if (monster.mapPosition() == t_mapPos)
            {
                return monster.stats();
            }
        }

        return {}; // default constructed MonsterStats are invalid with all zeros anyway
    }

    bool MonsterManager::damage(const MapPos_t & t_mapPos, const int t_damage)
    {
        for (Monster & monster : m_monsters)
        {
            if (monster.mapPosition() == t_mapPos)
            {
                monster.healthAdj(-t_damage);
                return !monster.isAlive();
            }
        }

        return false;
    }

    bool MonsterManager::removeDead(const Context & t_context)
    {
        bool wereAnyRemoved{ false };

        for (const Monster & monster : m_monsters)
        {
            if (!monster.isAlive())
            {
                t_context.maps.current().setObjectChar(monster.mapPosition(), ' ');
                wereAnyRemoved = true;
            }
        }

        if (wereAnyRemoved)
        {
            std::erase_if(m_monsters, [](const Monster & monster) { return !monster.isAlive(); });
        }

        return wereAnyRemoved;
    }

} // namespace castlecrawl