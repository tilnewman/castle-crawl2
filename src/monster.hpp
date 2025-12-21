#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED
//
// monster.hpp
//
#include "creature.hpp"
#include "map-types.hpp"
#include "monster-stats-database.hpp"
#include "spells.hpp"
#include "tile-image-enum.hpp"

#include <string>
#include <vector>

namespace castlecrawl
{
    struct Context;

    class Monster : public Creature
    {
      public:
        Monster(
            const Context & t_context,
            const std::size_t t_uniqueId,
            const MapPos_t & t_mapPos,
            const TileImage t_tileImage);

        virtual ~Monster() override = default;

        virtual CreatureAction takeTurn(const Context & t_context) override;

        [[nodiscard]] constexpr std::size_t uniqueId() const noexcept { return m_uniqueId; }

        [[nodiscard]] inline const MonsterStats stats() const noexcept { return m_stats; }

        [[nodiscard]] constexpr float healthRatio() const noexcept
        {
            if (m_stats.health_max <= 0)
            {
                return 0;
            }
            else
            {
                return (static_cast<float>(m_health) / static_cast<float>(m_stats.health_max));
            }
        }

        int healthAdj(const int t_adjustment);

        [[nodiscard]] constexpr bool isAlive() const noexcept { return (m_health > 0); }

      private:
        [[nodiscard]] const std::vector<Spell> spellsThereIsManaEnoughToCast() const;

        [[nodiscard]] CreatureAction decideWhichActionToTake(
            const Context & t_context, const std::vector<Spell> & t_spellsThatCanBeCast) const;

        void attackPlayer(const Context & t_context);

        void turnToFacePlayer(const Context & t_context);

      private:
        std::size_t m_uniqueId;
        MonsterStats m_stats;
        int m_health;
        int m_mana;
    };

} // namespace castlecrawl

#endif // MONSTER_HPP_INCLUDED