#ifndef MONSTER_MANAGER_HPP_INCLUDED
#define MONSTER_MANAGER_HPP_INCLUDED
//
// monster-manager.hpp
//
#include "map-types.hpp"
#include "tile-image-enum.hpp"

#include <vector>

namespace castlecrawl
{

    struct Context;

    //

    struct MapPosDist
    {
        MapPosDist(const MapPos_t & t_mapPos, const int t_distance)
            : position{ t_mapPos }
            , distance{ t_distance }
        {}

        MapPos_t position{ -1, -1 }; // both must be negative to be invalid
        int distance{ 0 };
    };

    //

    class Monster
    {
      public:
        Monster(const MapPos_t & t_mapPos, const TileImage t_tileImage);

        [[nodiscard]] inline const MapPos_t mapPosition() const noexcept { return m_mapPos; }
        [[nodiscard]] inline TileImage tileImage() const noexcept { return m_tileImage; }
        [[nodiscard]] bool isUndead() const;

        void takeTurn(const Context & t_context);

      private:
        [[nodiscard]] bool isPlayerAdjacent(const Context & t_context) const;
        void moveTowardPlayer(const Context & t_context);
        [[nodiscard]] int mapDistance(const MapPos_t & t_posA, const MapPos_t & t_posB) const;
        void moveTo(const Context & t_context, const MapPos_t & t_newMapPos);

      private:
        MapPos_t m_mapPos;
        TileImage m_tileImage;
    };

    //

    class MonsterManager
    {
      public:
        MonsterManager();

        void add(const Context & t_context, const MapPos_t & t_mapPos, const char t_mapChar);
        inline void reset() { m_monsters.clear(); }
        void takeTurns(const Context & t_context);

      private:
        std::vector<Monster>::iterator findMonsterFromMapPos(const MapPos_t & t_mapPos);

      private:
        std::vector<Monster> m_monsters;
    };

} // namespace castlecrawl

#endif // MONSTER_MANAGER_HPP_INCLUDED