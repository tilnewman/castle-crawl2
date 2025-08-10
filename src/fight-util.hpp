#ifndef FIGHT_UTIL_HPP_INCLUDED
#define FIGHT_UTIL_HPP_INCLUDED
//
// fight-util.hpp
//
#include "map-types.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace castlecrawl
{

    struct Context;

    [[nodiscard]] const sf::RectangleShape makeCreatureHealthBar(
        const Context & t_context, const float t_healthRatio, const MapPos_t & t_mapPos);

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

} // namespace castlecrawl

#endif // FIGHT_UTIL_HPP_INCLUDED