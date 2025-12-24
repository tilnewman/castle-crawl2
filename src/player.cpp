// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// player.cpp
//
#include "player.hpp"

#include "context.hpp"
#include "font.hpp"
#include "stats-display.hpp"

#include <cmath>

namespace castlecrawl
{

    Player::Player()
        : m_strength{ statStart, statMin, statMax }
        , m_dexterity{ statStart, statMin, statMax }
        , m_arcane{ statStart, statMin, statMax }
        , m_accuracy{ statStart, statMin, statMax }
        , m_luck{ statStart, statMin, statMax }
        , m_health{ healthStart }
        , m_healthMax{ healthStart }
        , m_mana{ manaStart }
        , m_manaMax{ manaStart }
        , m_level{ 0 }
        , m_experienceBase{ 0 }
        , m_experienceOffset{ 0 }
        , m_gold{ 0 }
        , m_maxGoldHeld{ 0 }
        , m_inventory{}
        , m_equipEffects{}
        , m_conditions{}
        , m_spells{ Spell::Spark, Spell::Frostbite, Spell::Zap } // spells known when game begins
        , m_spellLastCast{ Spell::Spark }
        , m_spellLastCastDir{ sf::Keyboard::Scan::Unknown } // any non-direction will work here
    {}

    void Player::updateEquipEffects()
    {
        m_accuracy.adjCurrent(-m_equipEffects.acc);
        m_arcane.adjCurrent(-m_equipEffects.arc);
        m_dexterity.adjCurrent(-m_equipEffects.dex);
        m_luck.adjCurrent(-m_equipEffects.lck);
        m_strength.adjCurrent(-m_equipEffects.str);

        m_equipEffects = m_inventory.totalEquipEffects();

        m_accuracy.adjCurrent(m_equipEffects.acc);
        m_arcane.adjCurrent(m_equipEffects.arc);
        m_dexterity.adjCurrent(m_equipEffects.dex);
        m_luck.adjCurrent(m_equipEffects.lck);
        m_strength.adjCurrent(m_equipEffects.str);
    }

    bool Player::hasCondition(const Condition t_condition) const
    {
        const auto foundIter{ std::find(
            std::begin(m_conditions), std::end(m_conditions), t_condition) };

        return (foundIter != std::end(m_conditions));
    }

    void Player::addCondition(const Condition t_condition)
    {
        if (!hasCondition(t_condition))
        {
            m_conditions.push_back(t_condition);
        }
    }

    void Player::removeCondition(const Condition t_condition)
    {
        std::erase(m_conditions, t_condition);
    }

    bool Player::hasSpell(const Spell t_spell) const
    {
        const auto foundIter{ std::find(std::begin(m_spells), std::end(m_spells), t_spell) };
        return (foundIter != std::end(m_spells));
    }

    void Player::addSpell(const Spell t_spell)
    {
        if (!hasSpell(t_spell))
        {
            m_spells.push_back(t_spell);
        }
    }

    int Player::experienceForLevel(const int t_level) const
    {
        if (t_level <= 0)
        {
            return 0;
        }
        else
        {
            int exp = (t_level * 200);

            exp +=
                static_cast<int>(sqrt(static_cast<float>(exp)) * static_cast<float>(t_level * 10));

            return exp;
        }
    }

    void Player::dumpInfo(const Context & t_context)
    {
        const std::size_t graphCount = 100;
        std::vector<int> experiencePerLevel;
        experiencePerLevel.reserve(graphCount);

        for (int index{ 0 }; index < static_cast<int>(graphCount); ++index)
        {
            experiencePerLevel.push_back(t_context.player.experienceForLevel(index));
        }

        util::StatsDisplay<int>::makeAndSavePNG(
            "exp-per-level", t_context.fonts.font(), experiencePerLevel);

        std::vector<int> experienceDeltas;
        experienceDeltas.reserve(experiencePerLevel.size());
        for (int index{ 0 }; index < static_cast<int>(experiencePerLevel.size() - 1); ++index)
        {
            experienceDeltas.push_back(
                experiencePerLevel.at(static_cast<std::size_t>(index + 1)) -
                experiencePerLevel.at(static_cast<std::size_t>(index)));
        }

        util::StatsDisplay<int>::makeAndSavePNG(
            "exp-per-level-delta", t_context.fonts.font(), experienceDeltas);
    }

} // namespace castlecrawl
