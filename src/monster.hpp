#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED
//
// monster.hpp
//
#include "creature.hpp"
#include "monster-stats-database.hpp"

#include <string>
#include <vector>

namespace castlecrawl
{
    struct Context;

    enum class MonsterAction
    {
        Attack,
        CastSpell,
        AcidSpray,
        PoisonBite,
        BreakWeapon,
        DevourArmor,
        BreatheFire
    };

    inline constexpr std::string_view monsterActionToName(const MonsterAction t_action) noexcept
    {
        // clang-format off
        switch(t_action)
        {
            case MonsterAction::Attack:         { return "Attack"; }
            case MonsterAction::CastSpell:      { return "CastSpell"; }
            case MonsterAction::AcidSpray:      { return "AcidSpray"; }
            case MonsterAction::PoisonBite:     { return "PoisonBite"; }
            case MonsterAction::BreakWeapon:    { return "BreakWeapon"; }
            case MonsterAction::DevourArmor:    { return "DevourArmor"; }
            case MonsterAction::BreatheFire:    
            default:                            { return "BreatheFire"; }
        }
        // clang-format on
    }

    struct MonsterActionEntry
    {
        MonsterActionEntry(const MonsterAction t_action, const float t_min, const float t_max)
            : action{ t_action }
            , min{ t_min }
            , max{ t_max }
        {}

        MonsterAction action;
        float min;
        float max;
    };

    class Monster : public Creature
    {
      public:
        Monster(const Context & t_context, const MapPos_t & t_mapPos, const TileImage t_tileImage);
        virtual ~Monster() override = default;

        // returns true if m_mapPos was changed
        virtual bool takeTurn(const Context & t_context) override;

        [[nodiscard]] inline const MonsterStats stats() const { return m_stats; }

        [[nodiscard]] inline float healthRatio() const noexcept
        {
            return (static_cast<float>(m_health) / static_cast<float>(m_stats.health_max));
        }

        int healthAdj(const int t_adjustment);

        [[nodiscard]] inline bool isAlive() const noexcept { return (m_health > 0); }

      private:
        [[nodiscard]] const std::vector<Spell> spellsThereIsManaEnoughToCast() const;

        [[nodiscard]] MonsterAction decideWhichActionToTake(
            const Context & t_context, const std::vector<Spell> & t_spellsThatCanBeCast) const;

        void attackPlayer(const Context & t_context);

      private:
        MonsterStats m_stats;
        int m_health;
        int m_mana;
    };

} // namespace castlecrawl

#endif // MONSTER_HPP_INCLUDED