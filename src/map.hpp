#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
//
// map.hpp
//
#include "game-config.hpp"
#include "map-types.hpp"
#include "quick-map.hpp"

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

namespace castlecrawl
{
    struct Context;

    class Map
    {
      public:
        Map();

        Map(const MapName name,
            const Context & context,
            const Floor floor,
            const MapChars_t & mapChars,
            const MapTransitions_t & transVec);

        MapName name() const { return m_name; }
        Floor floor() const { return m_floor; }
        const MapTransitions_t transitions() const { return m_transitions; }
        bool isEmpty() const { return m_map.empty(); }
        const sf::Vector2i size() const;
        bool isPosValid(const MapPos_t & pos) const;
        const MapCell cell(const MapPos_t & pos) const;
        void setObjectChar(const MapPos_t & pos, const char newChar);

        const MapPos_t
            screenPosToMapPos(const Context & context, const sf::Vector2f & screenPos) const;

        const sf::Vector2f
            mapPosToScreenPos(const Context & context, const MapPos_t & mapPos) const;

        const std::vector<MapCell> surroundingCellsHorizVert(const MapPos_t & pos) const;
        const std::vector<MapCell> surroundingCellsAll(const MapPos_t & pos) const;

        void dumpToConsole() const;

      private:
        MapName m_name;
        Map_t m_map;
        Floor m_floor;
        MapTransitions_t m_transitions;
    };

} // namespace castlecrawl

#endif // MAP_HPP_INCLUDED
