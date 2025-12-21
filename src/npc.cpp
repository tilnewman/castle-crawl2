// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// npc.cpp
//
#include "npc.hpp"

#include "context.hpp"
#include "maps.hpp"
#include "random.hpp"

namespace castlecrawl
{

    Npc::Npc(const Context & t_context, const MapPos_t & t_mapPos, const TileImage t_tileImage)
        : Creature{ t_context, t_mapPos, t_tileImage }
    {}

    CreatureAction Npc::takeTurn(const Context & t_context)
    {
        // only walk about a sixth of the time
        if (!isPlayerAdjacent(t_context) && (t_context.random.fromTo(1, 6) == 1))
        {
            std::vector<MapCell> adjacentCells =
                t_context.maps.current().surroundingCellsHorizVert(mapPosition());

            std::erase_if(adjacentCells, [](const MapCell & cell) {
                return (cell.object_char != tileImageToChar(TileImage::Empty));
            });

            if (!adjacentCells.empty())
            {
                moveTo(t_context, t_context.random.from(adjacentCells).position);
                return CreatureAction::Move;
            }
        }
        else if (t_context.random.fromTo(1, 4) == 1) // only turn some of the time if not walking
        {
            turn();
        }

        return CreatureAction::None;
    }

} // namespace castlecrawl