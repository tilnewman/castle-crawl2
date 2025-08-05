// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-manager.cpp
//
#include "monster-manager.hpp"

#include "context.hpp"
#include "maps.hpp"
#include "player-display.hpp"

namespace castlecrawl
{

    Monster::Monster(const MapPos_t & t_mapPos, const TileImage t_tileImage)
        : m_mapPos{ t_mapPos }
        , m_tileImage{ t_tileImage }
    {}

    void Monster::takeTurn(const Context & t_context)
    {
        if (!isPlayerAdjacent(t_context))
        {
            moveTowardPlayer(t_context);
        }
    }

    bool Monster::isPlayerAdjacent(const Context & t_context) const
    {
        const std::vector<MapCell> surroundingCells =
            t_context.maps.current().surroundingCellsAll(m_mapPos);

        const auto foundIter = std::find_if(
            std::begin(surroundingCells), std::end(surroundingCells), [&](const MapCell & cell) {
                return (t_context.player_display.position() == cell.position);
            });

        return (foundIter != std::end(surroundingCells));
    }

    void Monster::moveTowardPlayer(const Context & ) 
    {
        // todo
    }

    //

    MonsterManager::MonsterManager()
        : m_monsters{}
    {}

    void MonsterManager::add(const Context &, const MapPos_t & t_mapPos, const char t_mapChar)
    {
        m_monsters.emplace_back(t_mapPos, charToTileImage(t_mapChar));
    }

    void MonsterManager::takeTurns(const Context & t_context)
    {
        for (Monster & monster : m_monsters)
        {
            monster.takeTurn(t_context);
        }
    }

    std::vector<Monster>::iterator MonsterManager::findMonsterFromMapPos(const MapPos_t & t_mapPos)
    {
        for (auto iter{ std::begin(m_monsters) }; iter != std::end(m_monsters); ++iter)
        {
            if (iter->mapPosition() == t_mapPos)
            {
                return iter;
            }
        }

        return std::end(m_monsters);
    }

} // namespace castlecrawl