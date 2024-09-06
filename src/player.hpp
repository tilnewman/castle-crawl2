#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
//
// player.hpp
//
#include "inventory.hpp"
#include "stat.hpp"
#include "strong-types.hpp"

namespace castlecrawl
{

    class Player
    {
      public:
        Player();

        [[nodiscard]] Stat & strength() { return m_strength; }
        [[nodiscard]] Stat & dexterity() { return m_dexterity; }
        [[nodiscard]] Stat & accuracy() { return m_accuracy; }
        [[nodiscard]] Stat & luck() { return m_luck; }
        [[nodiscard]] Stat & arcane() { return m_arcane; }
        [[nodiscard]] Stat & health() { return m_health; }
        [[nodiscard]] Stat & mana() { return m_mana; }

        [[nodiscard]] int level() const { return m_level; }
        [[nodiscard]] int gold() const { return m_gold; }

        [[nodiscard]] Armor_t armor() const { return m_inventory.armorRating(); }

        void levelAdj(const int t_adj) { m_level += t_adj; }
        void goldAdj(const int t_adj) { m_gold += t_adj; }

        [[nodiscard]] item::Inventory & inventory() { return m_inventory; }

        void updateEquipEffects();
        [[nodiscard]] item::EquipEffect equipEffects() const { return m_equipEffects; }

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
        int m_gold;

        item::Inventory m_inventory;
        item::EquipEffect m_equipEffects;
    };

} // namespace castlecrawl

#endif // PLAYER_HPP_INCLUDED
