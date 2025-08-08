#ifndef MONSTER_STATS_DATABASE_HPP_INCLUDED
#define MONSTER_STATS_DATABASE_HPP_INCLUDED
//
// monster-stats-database.hpp
//
#include "tile-image-enum.hpp"

#include <map>
#include <vector>

namespace castlecrawl
{

    struct MonsterStats
    {
        [[nodiscard]] inline bool isValid() const noexcept { return (health > 0); }

        int health{ 0 };
        int mana{ 0 };
        int strength{ 0 };
        int dexterity{ 0 };
        int arcane{ 0 };
        int accuracy{ 0 };
        int luck{ 0 };
    };

    class MonsterStatsDatabase
    {
      public:
        MonsterStatsDatabase();

        void setup();
        void dumpInfo() const;

        [[nodiscard]] const MonsterStats stats(const TileImage & t_tileImage) const;

      private:
        void verifyAll() const;

      private:
        std::map<TileImage, MonsterStats> m_imageStatsMap;
    };

} // namespace castlecrawl

#endif // MONSTER_STATS_DATABASE_HPP_INCLUDED