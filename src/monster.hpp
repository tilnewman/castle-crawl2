#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED
//
// monster.hpp
//
#include "creature.hpp"
#include "monster-stats-database.hpp"

namespace castlecrawl
{
    struct Context;

    class Monster : public Creature
    {
      public:
        Monster(const Context & t_context, const MapPos_t & t_mapPos, const TileImage t_tileImage);
        virtual ~Monster() override = default;

        // returns true if m_mapPos was changed
        virtual bool takeTurn(const Context & t_context) override;

        [[nodiscard]] inline const MonsterStats stats() const { return m_stats; }

      private:
        MonsterStats m_stats;
    };

} // namespace castlecrawl

#endif // MONSTER_HPP_INCLUDED