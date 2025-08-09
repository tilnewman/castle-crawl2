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

    const sf::RectangleShape makeCreatureHealthBar(
        const Context & t_context, const float t_healthRatio, const MapPos_t & t_mapPos);

} // namespace castlecrawl

#endif // FIGHT_UTIL_HPP_INCLUDED