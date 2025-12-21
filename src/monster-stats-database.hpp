#ifndef MONSTER_STATS_DATABASE_HPP_INCLUDED
#define MONSTER_STATS_DATABASE_HPP_INCLUDED
//
// monster-stats-database.hpp
//
#include "spells.hpp"
#include "tile-image-enum.hpp"

#include <SFML/Graphics/Font.hpp>

#include <map>
#include <vector>

namespace castlecrawl
{
    struct Context;

    //

    struct MonsterStats
    {
        [[nodiscard]] constexpr bool isSpellCaster() const noexcept
        {
            return ((mana_max > 0) && (arcane > 0) && !spells.empty());
        }

        [[nodiscard]] constexpr bool isElemental() const noexcept
        {
            return (is_strong_to_ice_weak_to_fire || is_strong_to_fire_weak_to_ice);
        }

        // used as experince gained after killing a monster
        [[nodiscard]] int value() const;

        int health_max{ 0 };
        int mana_max{ 0 };

        int armor{ 0 };

        int strength{ 0 };
        int dexterity{ 0 };
        int arcane{ 0 };
        int accuracy{ 0 };
        int luck{ 0 };

        bool is_flying{ false };
        bool is_undead{ false };
        bool is_immune_to_nonmagical_weapons{ false };
        bool is_strong_to_ice_weak_to_fire{ false };
        bool is_strong_to_fire_weak_to_ice{ false };

        float breathe_fire_attack_ratio{ 0.0f };
        float poison_attack_ratio{ 0.0f };
        float acid_attack_ratio{ 0.0f };
        float spell_attack_ratio{ 0.0f };
        float break_attack_ratio{ 0.0f };
        float devour_attack_ratio{ 0.0f };

        std::vector<Spell> spells{};

        static constexpr int stat_max{ 100 };
    };

    //

    class MonsterStatsDatabase
    {
      public:
        MonsterStatsDatabase();

        void setup();
        void dumpInfo(const Context & t_context) const;

        [[nodiscard]] const MonsterStats find(const TileImage & t_tileImage) const;

      private:
        void verifyAll() const;
        void makeQuickReferenceImage(const Context & t_context) const;

      private:
        std::map<TileImage, MonsterStats> m_imageStatsMap;
    };

} // namespace castlecrawl

#endif // MONSTER_STATS_DATABASE_HPP_INCLUDED