// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster.cpp
//
#include "monster.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"

#include <algorithm>

namespace castlecrawl
{

    Monster::Monster(
        const Context & t_context, const MapPos_t & t_mapPos, const TileImage t_tileImage)
        : Creature{ t_mapPos, t_tileImage }
        , m_stats{ t_context.monster_stats.find(t_tileImage) }
        , m_health{ m_stats.health_max }
        , m_mana{ m_stats.mana_max }
    {}

    bool Monster::takeTurn(const Context & t_context)
    {
        if (!isPlayerAdjacent(t_context))
        {
            moveToward(t_context, t_context.player_display.position());
            m_actionString.clear();
            return true;
        }

        const std::vector<Spell> spellsThatCanBeCast = spellsThereIsManaToCast();
        const MonsterAction action = decideWhichActionToTake(t_context, spellsThatCanBeCast);
        m_actionString             = monsterActionToName(action);
        if (action == MonsterAction::CastSpell)
        {
            const Spell spellToCast = t_context.random.from(spellsThatCanBeCast);
            m_actionString += "_";
            m_actionString += spellToName(spellToCast);
        }

        return false;
    }

    MonsterAction Monster::decideWhichActionToTake(
        const Context & t_context, const std::vector<Spell> & t_spellsThatCanBeCast) const
    {
        std::vector<MonsterActionEntry> entries;

        float actionRatioSum = 0.0f;

        if (m_stats.breathe_fire_attack_ratio > 0.0f)
        {
            entries.push_back(MonsterActionEntry(
                MonsterAction::BreatheFire,
                actionRatioSum,
                (actionRatioSum + m_stats.breathe_fire_attack_ratio)));

            actionRatioSum += m_stats.breathe_fire_attack_ratio;
        }

        if (m_stats.poison_attack_ratio > 0.0f)
        {
            entries.push_back(MonsterActionEntry(
                MonsterAction::PoisonBite,
                actionRatioSum,
                (actionRatioSum + m_stats.poison_attack_ratio)));

            actionRatioSum += m_stats.poison_attack_ratio;
        }

        if (m_stats.acid_attack_ratio > 0.0f)
        {
            entries.push_back(MonsterActionEntry(
                MonsterAction::AcidSpray,
                actionRatioSum,
                (actionRatioSum + m_stats.acid_attack_ratio)));

            actionRatioSum += m_stats.acid_attack_ratio;
        }

        if (m_stats.break_attack_ratio > 0.0f)
        {
            entries.push_back(MonsterActionEntry(
                MonsterAction::BreakWeapon,
                actionRatioSum,
                (actionRatioSum + m_stats.break_attack_ratio)));

            actionRatioSum += m_stats.break_attack_ratio;
        }

        if (m_stats.devour_attack_ratio > 0.0f)
        {
            entries.push_back(MonsterActionEntry(
                MonsterAction::DevourArmor,
                actionRatioSum,
                (actionRatioSum + m_stats.devour_attack_ratio)));

            actionRatioSum += m_stats.devour_attack_ratio;
        }

        if (m_stats.isSpellCaster() && !t_spellsThatCanBeCast.empty())
        {
            entries.push_back(MonsterActionEntry(
                MonsterAction::CastSpell,
                actionRatioSum,
                (actionRatioSum + m_stats.spell_attack_ratio)));

            actionRatioSum += m_stats.spell_attack_ratio;
        }

        const float actionSelectRatio = t_context.random.fromTo(0.0f, 1.0f);
        for (const MonsterActionEntry & entry : entries)
        {
            if ((actionSelectRatio >= entry.min) && (actionSelectRatio <= entry.max))
            {
                return entry.action;
            }
        }

        return MonsterAction::Attack;
    }

    const std::vector<Spell> Monster::spellsThereIsManaToCast() const
    {
        std::vector<Spell> spells;

        for (const Spell spell : m_stats.spells)
        {
            if (spellToManaCost(spell) <= m_mana)
            {
                spells.push_back(spell);
            }
        }

        return spells;
    }

} // namespace castlecrawl