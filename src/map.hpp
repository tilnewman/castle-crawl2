#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
//
// map.hpp
//
#include "look-event.hpp"
#include "map-types.hpp"

#include <vector>

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
            const MapTransitions_t & t_transVec,
            const LookEvent & t_lookEvent = {});

        [[nodiscard]] constexpr MapName name() const noexcept { return m_name; }
        [[nodiscard]] constexpr Floor floor() const noexcept { return m_floor; }

        [[nodiscard]] inline const MapTransitions_t transitions() const noexcept
        {
            return m_transitions;
        }

        [[nodiscard]] constexpr bool isEmpty() const noexcept { return m_map.empty(); }
        [[nodiscard]] constexpr bool isDiscovered() const noexcept { return m_isDiscovered; }
        [[nodiscard]] const LookEvent lookEvent() const noexcept { return m_lookEvent; }

        [[nodiscard]] const sf::Vector2i size() const;
        [[nodiscard]] bool isPosValid(const MapPos_t & t_pos) const;
        [[nodiscard]] MapCell cell(const MapPos_t & t_pos) const;
        void setObjectChar(const MapPos_t & t_pos, const char t_newChar);

        constexpr void setDiscovered() noexcept { m_isDiscovered = true; }

        [[nodiscard]] MapPos_t
            screenPosToMapPos(const Context & t_context, const sf::Vector2f & t_screenPos) const;

        [[nodiscard]] sf::Vector2f
            mapPosToScreenPos(const Context & t_context, const MapPos_t & t_mapPos) const;

        [[nodiscard]] const std::vector<MapCell>
            surroundingCellsHorizVert(const MapPos_t & t_pos) const;
        [[nodiscard]] const std::vector<MapCell> surroundingCellsAll(const MapPos_t & t_pos) const;

        void dumpToConsole() const;

      private:
        MapName m_name;
        Map_t m_map;
        Floor m_floor;
        MapTransitions_t m_transitions;
        bool m_isDiscovered;
        LookEvent m_lookEvent;
    };

} // namespace castlecrawl

#endif // MAP_HPP_INCLUDED
