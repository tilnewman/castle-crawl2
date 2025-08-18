#ifndef FIGHT_UTIL_HPP_INCLUDED
#define FIGHT_UTIL_HPP_INCLUDED
//
// fight-util.hpp
//
#include "map-types.hpp"
#include "spells.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace castlecrawl
{
    struct Context;
}

namespace castlecrawl::fight
{

    struct HealthBarRectangles
    {
        sf::RectangleShape foreground;
        sf::RectangleShape background;
    };

    [[nodiscard]] const HealthBarRectangles makeCreatureHealthBars(
        const Context & t_context, const float t_healthRatio, const MapPos_t & t_mapPos);

    //

    struct RollResult
    {
        bool result{ false };
        bool lucky{ false };
        bool critical{ false };
    };

    // luck is NOT considered if t_challengerLuckValue==0
    [[nodiscard]] const RollResult rollRivalStats(
        const Context & t_context,
        const int t_challengerValue,
        const int t_defenderValue,
        const int t_challengerLuckValue = 0);

    //

    void damageMonster(
        const Context & t_context,
        const int t_damage,
        const RollResult & t_rollResult,
        const MapPos_t & t_monsterMapPos,
        const sf::Color & t_messageColor);

    void castSpell(
        const Context & t_context,
        const Spell t_spell,
        const MapPos_t & t_mapPos,
        const sf::Keyboard::Scancode t_direction);

} // namespace castlecrawl::fight

#endif // FIGHT_UTIL_HPP_INCLUDED