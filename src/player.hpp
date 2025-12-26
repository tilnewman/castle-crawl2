#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
//
// player.hpp
//
#include "condition.hpp"
#include "inventory.hpp"
#include "item-enums.hpp"
#include "json-wrapper.hpp"
#include "spells.hpp"
#include "stat.hpp"
#include "strong-types.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <algorithm>
#include <vector>

namespace castlecrawl
{

    struct Context;

    class Player
    {
      public:
        Player();

        void dumpInfo(const Context & t_context);

        [[nodiscard]] constexpr Stat & strength() noexcept { return m_strength; }
        [[nodiscard]] constexpr Stat & dexterity() noexcept { return m_dexterity; }
        [[nodiscard]] constexpr Stat & accuracy() noexcept { return m_accuracy; }
        [[nodiscard]] constexpr Stat & luck() noexcept { return m_luck; }
        [[nodiscard]] constexpr Stat & arcane() noexcept { return m_arcane; }

        [[nodiscard]] constexpr int health() const noexcept { return m_health; }
        [[nodiscard]] constexpr int healthMax() const noexcept { return m_healthMax; }
        [[nodiscard]] constexpr int mana() const noexcept { return m_mana; }
        [[nodiscard]] constexpr int manaMax() const noexcept { return m_manaMax; }
        [[nodiscard]] constexpr int level() const noexcept { return m_level; }
        [[nodiscard]] constexpr int gold() const noexcept { return m_gold; }
        [[nodiscard]] constexpr int goldMaxHeld() const noexcept { return m_maxGoldHeld; }
        [[nodiscard]] constexpr int experienceOffset() const noexcept { return m_experienceOffset; }

        [[nodiscard]] constexpr int experience() const noexcept
        {
            return (m_experienceBase + m_experienceOffset);
        }

        [[nodiscard]] int experienceForLevel(const int t_level) const;

        [[nodiscard]] inline int experienceForNextLevel() const
        {
            return experienceForLevel(m_level + 1);
        }

        [[nodiscard]] inline const Armor_t armor() const noexcept
        {
            return m_inventory.armorRating();
        }

        inline void levelAdvance()
        {
            advanceExperienceForLevel();
            ++m_level;
        }

        constexpr void experinceAdj(const int t_ad) noexcept { m_experienceOffset += t_ad; }
        constexpr void healthMaxAdj(const int t_adj) noexcept { m_healthMax += t_adj; }
        constexpr void manaMaxAdj(const int t_adj) noexcept { m_manaMax += t_adj; }

        constexpr void goldAdj(const int t_adj) noexcept
        {
            m_gold += t_adj;

            if (m_gold < 0)
            {
                m_gold = 0;
            }

            if (m_gold > m_maxGoldHeld)
            {
                m_maxGoldHeld = m_gold;
            }
        }

        constexpr void healthAdj(const int t_adj)
        {
            m_health = std::clamp((m_health + t_adj), 0, m_healthMax);
        }

        constexpr void manaAdj(const int t_adj)
        {
            m_mana = std::clamp((m_mana + t_adj), 0, m_manaMax);
        }

        [[nodiscard]] inline item::Inventory & inventory() noexcept { return m_inventory; }

        void updateEquipEffects();
        [[nodiscard]] inline const item::EquipEffect equipEffects() const noexcept
        {
            return m_equipEffects;
        }

        [[nodiscard]] inline const std::vector<Condition> conditions() const noexcept
        {
            return m_conditions;
        }

        [[nodiscard]] bool hasCondition(const Condition t_condition) const;
        void addCondition(const Condition t_condition);
        void removeCondition(const Condition t_condition);

        [[nodiscard]] inline const std::vector<Spell> spells() const noexcept { return m_spells; }
        [[nodiscard]] bool hasSpell(const Spell t_spell) const;
        void addSpell(const Spell t_spell);

        [[nodiscard]] constexpr Spell spellLastCast() const noexcept { return m_spellLastCast; }

        [[nodiscard]] inline sf::Keyboard::Scancode spellLastCastDir() const noexcept
        {
            return m_spellLastCastDir;
        }

        constexpr void
            setSpellLastCast(const Spell t_spell, const sf::Keyboard::Scancode t_dir) noexcept
        {
            m_spellLastCast    = t_spell;
            m_spellLastCastDir = t_dir;
        }

        friend void to_json(nlohmann::json & j, const Player & p);
        friend void from_json(const nlohmann::json & j, Player & p);

      private:
        void advanceExperienceForLevel()
        {
            const int expForLevel = (experienceForLevel(m_level + 1) - experienceForLevel(m_level));
            m_experienceBase += expForLevel;
            m_experienceOffset -= expForLevel;
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

        int m_health;
        int m_healthMax;
        int m_mana;
        int m_manaMax;

        int m_level;
        int m_experienceBase;
        int m_experienceOffset;
        int m_gold;
        int m_maxGoldHeld;

        item::Inventory m_inventory;
        item::EquipEffect m_equipEffects;
        std::vector<Condition> m_conditions;
        std::vector<Spell> m_spells;

        Spell m_spellLastCast;
        sf::Keyboard::Scancode m_spellLastCastDir;
    };

    inline void to_json(nlohmann::json & j, const Player & p)
    {
        j = nlohmann::json{ { "strength", p.m_strength },
                            { "dexterity", p.m_dexterity },
                            { "arcane", p.m_arcane },
                            { "accuracy", p.m_accuracy },
                            { "luck", p.m_luck },
                            { "health", p.m_health },
                            { "healthMax", p.m_healthMax },
                            { "mana", p.m_mana },
                            { "manaMax", p.m_manaMax },
                            { "level", p.m_level },
                            { "experienceBase", p.m_experienceBase },
                            { "experienceOffset", p.m_experienceOffset },
                            { "gold", p.m_gold },
                            { "maxGoldHeld", p.m_maxGoldHeld },
                            { "inventory", p.m_inventory },
                            { "equipEffects", p.m_equipEffects },
                            { "conditions", p.m_conditions },
                            { "spells", p.m_spells },
                            { "spellLastCast", p.m_spellLastCast },
                            { "spellLastCastDir", p.m_spellLastCastDir } };
    }

    inline void from_json(const nlohmann::json & j, Player & p)
    {
        j.at("strength").get_to(p.m_strength);
        j.at("dexterity").get_to(p.m_dexterity);
        j.at("arcane").get_to(p.m_arcane);
        j.at("accuracy").get_to(p.m_accuracy);
        j.at("luck").get_to(p.m_luck);
        j.at("health").get_to(p.m_health);
        j.at("healthMax").get_to(p.m_healthMax);
        j.at("mana").get_to(p.m_mana);
        j.at("manaMax").get_to(p.m_manaMax);
        j.at("level").get_to(p.m_level);
        j.at("experienceBase").get_to(p.m_experienceBase);
        j.at("experienceOffset").get_to(p.m_experienceOffset);
        j.at("gold").get_to(p.m_gold);
        j.at("maxGoldHeld").get_to(p.m_maxGoldHeld);
        j.at("inventory").get_to(p.m_inventory);
        j.at("equipEffects").get_to(p.m_equipEffects);
        j.at("conditions").get_to(p.m_conditions);
        j.at("spells").get_to(p.m_spells);
        j.at("spellLastCast").get_to(p.m_spellLastCast);
        j.at("spellLastCastDir").get_to(p.m_spellLastCastDir);
    }

} // namespace castlecrawl

#endif // PLAYER_HPP_INCLUDED
