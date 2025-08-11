// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// player.cpp
//
#include "player.hpp"

#include <algorithm>

namespace castlecrawl
{

    Player::Player()
        : m_strength{ statStart, statMin, statMax }
        , m_dexterity{ statStart, statMin, statMax }
        , m_arcane{ statStart, statMin, statMax }
        , m_accuracy{ statStart, statMin, statMax }
        , m_luck{ statStart, statMin, statMax }
        , m_health{ healthStart, 0, healthStart }
        , m_mana{ manaStart, 0, manaStart }
        , m_level{ 1 }
        , m_gold{ 0 }
        , m_inventory{}
        , m_equipEffects{}
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

} // namespace castlecrawl
