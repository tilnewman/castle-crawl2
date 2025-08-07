// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// npc.cpp
//
#include "npc.hpp"

#include "context.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"

#include <algorithm>

namespace castlecrawl
{

    Npc::Npc(const MapPos_t & t_mapPos, const TileImage t_tileImage)
        : Creature{ t_mapPos, t_tileImage }
    {}

    bool Npc::takeTurn(const Context & t_context)
    {
        // only walk about a sixth of the time
        if (!isPlayerAdjacent(t_context) && (t_context.random.fromTo(1, 6) == 1))
        {
            std::vector<MapCell> adjacentCells =
                t_context.maps.current().surroundingCellsHorizVert(mapPosition());

            std::erase_if(
                adjacentCells, [](const MapCell & cell) { return (cell.object_char != ' '); });

            if (!adjacentCells.empty())
            {
                moveTo(t_context, t_context.random.from(adjacentCells).position);
                return true;
            }
        }

        return false;
    }

} // namespace castlecrawl