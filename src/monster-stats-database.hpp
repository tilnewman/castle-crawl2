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
        [[nodiscard]] inline bool isValid() const noexcept
        {
            // only mana,luck,arcane are allowed to be zero
            return ((health > 0) && (strength > 0) && (dexterity > 0) && (accuracy > 0));
        }

        [[nodiscard]] inline bool isSpellCaster() const noexcept
        {
            return ((mana > 0) && (arcane > 0));
        }

        int health{ 0 };
        int mana{ 0 };
        int strength{ 0 };
        int dexterity{ 0 };
        int arcane{ 0 };
        int accuracy{ 0 };
        int luck{ 0 };

        bool is_flying{ false };
        bool is_undead{ false };
        bool is_immune_to_nonmagical_weapons{ false };

        float breathe_fire_attack_ratio{ 0.0f };
        float poison_attack_ratio{ 0.0f };
        float acid_attack_ratio{ 0.0f };
        float spell_attack_ratio{ 0.0f };
        float break_attack_ratio{ 0.0f };
        float devour_attack_ratio{ 0.0f };

        // stun/immobilize/terror/stone/slowed
    };

    class MonsterStatsDatabase
    {
      public:
        MonsterStatsDatabase();

        void setup();
        void dumpInfo() const;

        [[nodiscard]] const MonsterStats find(const TileImage & t_tileImage) const;

      private:
        void verifyAll() const;

      private:
        std::map<TileImage, MonsterStats> m_imageStatsMap;
    };

} // namespace castlecrawl

#endif // MONSTER_STATS_DATABASE_HPP_INCLUDED