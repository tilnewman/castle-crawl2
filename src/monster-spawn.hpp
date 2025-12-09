#ifndef MONSTER_SPAWN_HPP_INCLUDED
#define MONSTER_SPAWN_HPP_INCLUDED
//
// monster-spawn.hpp
//
#include "tile-image-enum.hpp"

namespace castlecrawl
{

    struct Context;

    //

    struct MonsterSpawn
    {
        [[nodiscard]] static TileImage randomMonster(const Context & t_context);
    };

} // namespace castlecrawl

#endif // MONSTER_SPAWN_HPP_INCLUDED
