#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
//
// player.hpp
//
#include "condition.hpp"
#include "inventory.hpp"
#include "map-types.hpp"
#include "spells.hpp"
#include "stat.hpp"
#include "strong-types.hpp"

#include <vector>

namespace castlecrawl
{

    class Player
    {
      public:
        Player();

        [[nodiscard]] inline Stat & strength() noexcept { return m_strength; }
        [[nodiscard]] inline Stat & dexterity() noexcept { return m_dexterity; }
        [[nodiscard]] inline Stat & accuracy() noexcept { return m_accuracy; }
        [[nodiscard]] inline Stat & luck() noexcept { return m_luck; }
        [[nodiscard]] inline Stat & arcane() noexcept { return m_arcane; }

        [[nodiscard]] inline Stat & health() noexcept { return m_health; }
        [[nodiscard]] inline Stat & mana() noexcept { return m_mana; }

        [[nodiscard]] inline int level() const noexcept { return m_level; }
        [[nodiscard]] inline int experience() const noexcept { return m_experience; }
        [[nodiscard]] inline int gold() const noexcept { return m_gold; }

        [[nodiscard]] int experienceForLevel(const int t_level) const;

        [[nodiscard]] inline int experienceForNextLevel() const
        {
            return experienceForLevel(m_level + 1);
        }

        [[nodiscard]] inline Armor_t armor() const noexcept { return m_inventory.armorRating(); }

        inline void levelAdj(const int t_adj) { m_level += t_adj; }
        inline void experinceAdj(const int t_ad) { m_experience += t_ad; }
        inline void goldAdj(const int t_adj) { m_gold += t_adj; }

        [[nodiscard]] inline item::Inventory & inventory() noexcept { return m_inventory; }

        void updateEquipEffects();
        [[nodiscard]] inline item::EquipEffect equipEffects() const noexcept
        {
            return m_equipEffects;
        }

        [[nodiscard]] inline const std::vector<Condition> conditions() const
        {
            return m_conditions;
        }

        [[nodiscard]] bool hasCondition(const Condition t_condition) const;
        void addCondition(const Condition t_condition);
        void removeCondition(const Condition t_condition);

        [[nodiscard]] inline const std::vector<Spell> spells() const { return m_spells; }
        [[nodiscard]] bool hasSpell(const Spell t_spell) const;
        void addSpell(const Spell t_spell);

        [[nodiscard]] inline Spell spellLastCast() const { return m_spellLastCast; }
        [[nodiscard]] inline MapPos_t spellLastCastPos() const { return m_spellLastCastPos; }

        inline void setSpellLastCast(const Spell t_spell, const MapPos_t & t_mapPos)
        {
            m_spellLastCast    = t_spell;
            m_spellLastCastPos = t_mapPos;
        }

      private:
        constexpr static int statMin     = 1;
        constexpr static int statMax     = 100;
        constexpr static int statStart   = 10;
        constexpr static int healthStart = 20;
        constexpr static int manaStart   = 10;

        Stat m_strength;
        Stat m_dexterity;
        Stat m_arcane;
        Stat m_accuracy;
        Stat m_luck;

        // these two will never have a current value that strays from the normal
        Stat m_health;
        Stat m_mana;

        int m_level;
        int m_experience;
        int m_gold;

        item::Inventory m_inventory;
        item::EquipEffect m_equipEffects;
        std::vector<Condition> m_conditions;
        std::vector<Spell> m_spells;

        Spell m_spellLastCast;
        MapPos_t m_spellLastCastPos;
    };

} // namespace castlecrawl

#endif // PLAYER_HPP_INCLUDED
