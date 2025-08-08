// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster.cpp
//
#include "monster.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"

#include <algorithm>

namespace castlecrawl
{

    Monster::Monster(
        const Context & t_context, const MapPos_t & t_mapPos, const TileImage t_tileImage)
        : Creature{ t_mapPos, t_tileImage }
        , m_stats{ t_context.monster_stats.find(t_tileImage) }
    {
        M_CHECK(
            m_stats.isValid(),
            "MonsterStatsDatabase failed to find " << tileImageToName(t_tileImage));
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
            moveToward(t_context, t_context.player_display.position());
            return true;
        }
    }

} // namespace castlecrawl