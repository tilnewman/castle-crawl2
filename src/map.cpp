// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// map.cpp
//
#include "map.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "quick-map.hpp"
#include "random.hpp"
#include "sfml-util.hpp"

#include <iostream>

namespace castlecrawl
{

    Map::Map()
        : m_name{ MapName::Level_1_BoilerRoom } // anything works here
        , m_map{}
        , m_floor{ Floor::Dirt } // anything works here
        , m_transitions{}
        , m_isDiscovered{ false }
    {}

    Map::Map(
        const MapName t_name,
        const Context & t_context,
        const Floor t_floor,
        const MapChars_t & t_mapChars,
        const MapTransitions_t & t_transVec)
        : m_name{ t_name }
        , m_map{}
        , m_floor{ t_floor }
        , m_transitions{ t_transVec }
        , m_isDiscovered{ false }
    {
        const QuickMap quickMap(t_context.config, t_mapChars);

        const sf::Vector2i size = quickMap.size();

        for (int y(0); y < size.y; ++y)
        {
            m_map.push_back({});

            for (int x(0); x < size.x; ++x)
            {
                MapCell cell;
                cell.position    = { x, y };
                cell.object_char = quickMap.getChar(x, y);

                // put random floor tiles under everything except edges
                if (cell.object_char != '.')
                {
                    if (Floor::Stone == m_floor)
                    {
                        cell.floor_char = '\x6';
                        cell.floor_char += t_context.random.fromTo<char>(0, 5);
                    }
                    else if (Floor::Wood == m_floor)
                    {
                        cell.floor_char = '\x0';
                        cell.floor_char += t_context.random.fromTo<char>(0, 5);
                    }
                    else // dirt
                    {
                        cell.floor_char = '\xC';
                        cell.floor_char += t_context.random.fromTo<char>(0, 4);
                    }
                }

                m_map.back().push_back(cell);
            }
        }
    }

    const sf::Vector2i Map::size() const
    {
        if (isEmpty())
        {
            return { 0, 0 };
        }
        else
        {
            return sf::Vector2i{ static_cast<int>(m_map.front().size()),
                                 static_cast<int>(m_map.size()) };
        }
    }

    bool Map::isPosValid(const MapPos_t & t_pos) const
    {
        if (isEmpty())
        {
            return false;
        }
        else
        {
            const sf::Vector2i sizes = size();
            return ((t_pos.x >= 0) && (t_pos.y >= 0) && (t_pos.x < sizes.x) && (t_pos.y < sizes.y));
        }
    }

    MapCell Map::cell(const MapPos_t & t_posParam) const
    {
        if (!isPosValid(t_posParam))
        {
            return {}; // MapCell default values are both safe and invalid
        }

        const sf::Vector2s pos{ t_posParam };
        return m_map[pos.y][pos.x];
    }

    void Map::setObjectChar(const MapPos_t & t_posParam, const char t_newChar)
    {
        if (!isPosValid(t_posParam))
        {
            return;
        }

        const sf::Vector2s pos{ t_posParam };
        m_map[pos.y][pos.x].object_char = t_newChar;
    }

    MapPos_t
        Map::screenPosToMapPos(const Context & t_context, const sf::Vector2f & t_screenPos) const
    {
        const sf::FloatRect mapRect = t_context.layout.mapRect();
        sf::Vector2f pos            = mapRect.position;

        const sf::Vector2i mapSize = size();
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const sf::FloatRect cellRect(pos, t_context.layout.cellSize());
                if (cellRect.contains(t_screenPos))
                {
                    return { x, y };
                }

                pos.x += t_context.layout.cellSize().x;
            }

            pos.x = mapRect.position.x;
            pos.y += t_context.layout.cellSize().y;
        }

        return { -1, -1 }; // any negative values work here
    }

    sf::Vector2f Map::mapPosToScreenPos(const Context & t_context, const MapPos_t & t_mapPos) const
    {
        return (
            t_context.layout.mapRect().position +
            (t_context.layout.cellSize() * sf::Vector2f{ t_mapPos }));
    }

    const std::vector<MapCell> Map::surroundingCellsHorizVert(const MapPos_t & t_pos) const
    {
        std::vector<MapCell> cells;
        cells.reserve(4);

        if (const MapPos_t posAbove(t_pos.x, (t_pos.y - 1)); isPosValid(posAbove))
        {
            cells.push_back(cell(posAbove));
        }

        if (const MapPos_t posBelow(t_pos.x, (t_pos.y + 1)); isPosValid(posBelow))
        {
            cells.push_back(cell(posBelow));
        }

        if (const MapPos_t posRight((t_pos.x + 1), t_pos.y); isPosValid(posRight))
        {
            cells.push_back(cell(posRight));
        }

        if (const MapPos_t posLeft((t_pos.x - 1), t_pos.y); isPosValid(posLeft))
        {
            cells.push_back(cell(posLeft));
        }

        return cells;
    }

    const std::vector<MapCell> Map::surroundingCellsAll(const MapPos_t & t_pos) const
    {
        std::vector<MapCell> cells;
        cells.reserve(8);

        for (int y(t_pos.y - 1); y <= (t_pos.y + 1); ++y)
        {
            for (int x(t_pos.x - 1); x <= (t_pos.x + 1); ++x)
            {
                const MapPos_t position(x, y);
                if (position == t_pos)
                {
                    continue;
                }

                if (!isPosValid(position))
                {
                    continue;
                }

                cells.push_back(cell(position));
            }
        }

        return cells;
    }

    void Map::dumpToConsole() const
    {
        for (const std::vector<MapCell> & cellRow : m_map)
        {
            for (const MapCell cell : cellRow)
            {
                std::cout << cell.object_char;
            }

            std::cout << std::endl;
        }
    }

} // namespace castlecrawl
