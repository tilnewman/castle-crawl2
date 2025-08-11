// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster.cpp
//
#include "monster.hpp"

#include "animation-manager.hpp"
#include "check-macros.hpp"
#include "context.hpp"
#include "fight-util.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "random.hpp"
#include "rising-text-anim.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

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
            return true;
        }

        const std::vector<Spell> spellsThatCanBeCast{ spellsThereIsManaEnoughToCast() };
        const MonsterAction action{ decideWhichActionToTake(t_context, spellsThatCanBeCast) };

        if (action == MonsterAction::CastSpell)
        {
            const Spell spellToCast{ t_context.random.from(spellsThatCanBeCast) };
            m_mana -= spellToManaCost(spellToCast);

            std::string actionMessage{ " Casts " };
            actionMessage += spellToName(spellToCast);

            t_context.anim.risingText().add(
                t_context, actionMessage, t_context.config.message_color_cast_spell, mapPosition());
        }
        else if (action == MonsterAction::Attack)
        {
            attackPlayer(t_context);
        }

        return false;
    }

    void Monster::attackPlayer(const Context & t_context)
    {
        const RollResult roll{ rollRivalStats(
            t_context, m_stats.accuracy, t_context.player.dexterity().current(), m_stats.luck) };

        if (!roll.result)
        {
            t_context.anim.risingText().add(
                t_context, "miss", t_context.config.message_color_attack_miss, mapPosition());

            return;
        }

        // calc damage
        const int damageMin{ 1 + (m_stats.strength / 10) };
        const int damageMax{ std::max((damageMin + 1), m_stats.strength) };
        int damage{ t_context.random.fromTo(damageMin, damageMax) };

        damage -= t_context.player.armor().as<int>();
        if (damage < 0)
        {
            damage = 0;
        }

        if (0 == damage)
        {
            t_context.anim.risingText().add(
                t_context, "miss armor", t_context.config.message_color_attack_miss, mapPosition());
        }
        else
        {
            std::string actionMessage{ std::to_string(damage) };
            actionMessage += " dmg";

            t_context.anim.risingText().add(
                t_context, actionMessage, t_context.config.message_color_attack_hit, mapPosition());

            t_context.player_display.shake();
            t_context.player_display.bloodSplatStart(t_context);

            t_context.player.health().adjCurrent(-damage);
            t_context.top_panel.update(t_context);
        }
    }

    MonsterAction Monster::decideWhichActionToTake(
        const Context & t_context, const std::vector<Spell> & t_spellsThatCanBeCast) const
    {
        std::vector<MonsterActionEntry> entries;

        float actionRatioSum{ 0.0f };

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

    int Monster::healthAdj(const int t_adjustment)
    {
        m_health = std::clamp((m_health + t_adjustment), 0, MonsterStats::stat_max);
        return m_health;
    }

    const std::vector<Spell> Monster::spellsThereIsManaEnoughToCast() const
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