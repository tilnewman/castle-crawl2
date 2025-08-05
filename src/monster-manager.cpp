// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-manager.cpp
//
#include "monster-manager.hpp"

#include "context.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"

#include <algorithm>

namespace castlecrawl
{

    Monster::Monster(const MapPos_t & t_mapPos, const TileImage t_tileImage)
        : m_mapPos{ t_mapPos }
        , m_tileImage{ t_tileImage }
    {}

    bool Monster::isUndead() const
    {
        return (
            (m_tileImage == TileImage::SkullSlime) || (m_tileImage == TileImage::BoneDragon) ||
            (m_tileImage == TileImage::RottingChomper) ||
            (m_tileImage == TileImage::FleshCreeper) || (m_tileImage == TileImage::GreenWight) ||
            (m_tileImage == TileImage::SoulEater) || (m_tileImage == TileImage::BoneHound) ||
            (m_tileImage == TileImage::Siren) || (m_tileImage == TileImage::Specter) ||
            (m_tileImage == TileImage::BoneHydra) || (m_tileImage == TileImage::ShadowFiend) ||
            (m_tileImage == TileImage::Revenant) || (m_tileImage == TileImage::Lorocyproca) ||
            (m_tileImage == TileImage::HellWing) || (m_tileImage == TileImage::Hellion));
    }

    bool Monster::takeTurn(const Context & t_context)
    {
        if (isPlayerAdjacent(t_context))
        {
            // todo attack or something
            return false;
        }
        else
        {
            moveTowardPlayer(t_context);
            return true;
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

    void Monster::moveTowardPlayer(const Context & t_context)
    {
        const std::vector<MapCell> adjacentCells =
            t_context.maps.current().surroundingCellsHorizVert(m_mapPos);

        const MapPos_t playerPos = t_context.player_display.position();

        std::vector<PositionDistance> positions;
        positions.reserve(adjacentCells.size());

        for (const MapCell & cell : adjacentCells)
        {
            if (cell.object_char == ' ')
            {
                positions.emplace_back(cell.position, distance(playerPos, cell.position));
            }
        }

        std::sort(
            std::begin(positions),
            std::end(positions),
            [](const PositionDistance & a, const PositionDistance & b) {
                return (a.distance < b.distance);
            });

        if (positions.empty())
        {
            // there are no adjacent valid and empty cells, so do nothing
            return;
        }

        const int closestDistance = positions.front().distance;

        std::erase_if(positions, [&](const PositionDistance & mpd) {
            return (mpd.distance != closestDistance);
        });

        moveTo(t_context, t_context.random.from(positions).position);
    }

    void Monster::moveTo(const Context & t_context, const MapPos_t & t_newMapPos)
    {
        const char myChar = t_context.maps.current().cell(m_mapPos).object_char;
        t_context.maps.current().setObjectChar(m_mapPos, ' ');
        m_mapPos = t_newMapPos;
        t_context.maps.current().setObjectChar(m_mapPos, myChar);
    }

    //

    MonsterManager::MonsterManager()
        : m_monsters{}
    {}

    void MonsterManager::add(const Context &, const MapPos_t & t_mapPos, const char t_mapChar)
    {
        m_monsters.emplace_back(t_mapPos, charToTileImage(t_mapChar));
    }

    bool MonsterManager::takeTurns(const Context & t_context)
    {
        bool didAnyMonstersMove = false;
        for (Monster & monster : m_monsters)
        {
            if (monster.takeTurn(t_context))
            {
                didAnyMonstersMove = true;
            }
        }

        return didAnyMonstersMove;
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