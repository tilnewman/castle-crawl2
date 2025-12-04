#ifndef QUICKMAP_HPP_INCLUDED
#define QUICKMAP_HPP_INCLUDED
//
// quick-map.hpp
//
#include "game-config.hpp"
#include "map-types.hpp"

#include <SFML/System/Vector2.hpp>

namespace castlecrawl
{
    // QuickMaps are the maps found in the source code in maps.cpp. They are temporary
    // placeholders for real maps that are easy for humans to manage and are easily
    // convertible into real maps. This class is responsible for loading these temp
    // maps, and then converting them into real maps.
    class QuickMap
    {
      public:
        QuickMap(const GameConfig & t_config, const MapChars_t & t_mapChars);

        [[nodiscard]] constexpr bool empty() const noexcept { return m_mapChars.empty(); }

        // assumes all rows are the same length, see convertQuickMapToRealMap_VerifySize()
        [[nodiscard]] inline const sf::Vector2i size() const
        {
            return sf::Vector2i{ static_cast<int>(m_mapChars.front().size()),
                                 static_cast<int>(m_mapChars.size()) };
        }

        [[nodiscard]] inline bool isPosValid(const MapPos_t & t_pos) const
        {
            return (
                (t_pos.x >= 0) && (t_pos.y >= 0) && (t_pos.x < static_cast<int>(size().x)) &&
                (t_pos.y < static_cast<int>(size().y)));
        }

        [[nodiscard]] char getChar(const int t_x, const int t_y) const;

        inline void setChar(const int t_x, const int t_y, const char t_ch)
        {
            m_mapChars.at(static_cast<std::size_t>(t_y)).at(static_cast<std::size_t>(t_x)) = t_ch;
        }

        void dumpToConsole() const;

      private:
        void convertQuickMapToRealMap(const GameConfig & t_config);
        void convertQuickMapToRealMap_VerifySize(const GameConfig & t_config) const;
        void convertQuickMapToRealMap_Walls();
        void convertQuickMapToRealMap_WallCorners();

      private:
        MapChars_t m_mapChars;
    };

} // namespace castlecrawl

#endif // QUICKMAP_HPP_INCLUDED
