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

        Map(const MapName t_name,
            const Context & t_context,
            const Floor t_floor,
            const MapChars_t & t_mapChars,
            const MapTransitions_t & t_transVec);

        [[nodiscard]] inline MapName name() const { return m_name; }
        [[nodiscard]] inline Floor floor() const { return m_floor; }
        [[nodiscard]] inline MapTransitions_t transitions() const { return m_transitions; }
        [[nodiscard]] bool isEmpty() const { return m_map.empty(); }
        [[nodiscard]] sf::Vector2i size() const;
        [[nodiscard]] bool isPosValid(const MapPos_t & t_pos) const;
        [[nodiscard]] MapCell cell(const MapPos_t & t_pos) const;
        void setObjectChar(const MapPos_t & t_pos, const char t_newChar);

        [[nodiscard]] MapPos_t
            screenPosToMapPos(const Context & t_context, const sf::Vector2f & t_screenPos) const;

        [[nodiscard]] sf::Vector2f
            mapPosToScreenPos(const Context & t_context, const MapPos_t & t_mapPos) const;

        [[nodiscard]] std::vector<MapCell> surroundingCellsHorizVert(const MapPos_t & t_pos) const;
        [[nodiscard]] std::vector<MapCell> surroundingCellsAll(const MapPos_t & t_pos) const;

        void dumpToConsole() const;

      private:
        MapName m_name;
        Map_t m_map;
        Floor m_floor;
        MapTransitions_t m_transitions;
    };

} // namespace castlecrawl

#endif // MAP_HPP_INCLUDED
