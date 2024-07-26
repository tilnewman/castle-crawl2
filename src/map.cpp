// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// map.cpp
//
#include "map.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "random.hpp"
#include "sfml-util.hpp"

#include <iostream>

namespace castlecrawl
{

    Map::Map()
        : m_name(MapName::Level_1_BoilerRoom) // anything works here
        , m_map()
        , m_floor(Floor::Dirt) // anything works here
        , m_transitions()
    {}

    Map::Map(
        const MapName name,
        const Context & context,
        const Floor floor,
        const MapChars_t & mapChars,
        const MapTransitions_t & transVec)
        : m_name(name)
        , m_map()
        , m_floor(floor)
        , m_transitions(transVec)
    {
        const QuickMap quickMap(context.config, mapChars);

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
                        cell.floor_char += context.random.fromTo<char>(0, 5);
                    }
                    else if (Floor::Wood == m_floor)
                    {
                        cell.floor_char = '\x0';
                        cell.floor_char += context.random.fromTo<char>(0, 5);
                    }
                    else // dirt
                    {
                        cell.floor_char = '\xC';
                        cell.floor_char += context.random.fromTo<char>(0, 4);
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

    bool Map::isPosValid(const MapPos_t & pos) const
    {
        if (isEmpty())
        {
            return false;
        }
        else
        {
            const sf::Vector2i sizes = size();
            return ((pos.x >= 0) && (pos.y >= 0) && (pos.x < sizes.x) && (pos.y < sizes.y));
        }
    }

    const MapCell Map::cell(const MapPos_t & posParam) const
    {
        if (!isPosValid(posParam))
        {
            return {}; // MapCell default values are both safe and invalid
        }

        const sf::Vector2s pos{ posParam };
        return m_map[pos.y][pos.x];
    }

    void Map::setObjectChar(const MapPos_t & posParam, const char newChar)
    {
        if (!isPosValid(posParam))
        {
            return;
        }

        const sf::Vector2s pos{ posParam };
        m_map[pos.y][pos.x].object_char = newChar;
    }

    const MapPos_t
        Map::screenPosToMapPos(const Context & context, const sf::Vector2f & screenPos) const
    {
        const sf::FloatRect mapRect = context.layout.mapRect();
        sf::Vector2f pos            = util::position(mapRect);

        const sf::Vector2i mapSize = size();
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const sf::FloatRect cellRect(pos, context.layout.cellSize());
                if (cellRect.contains(screenPos))
                {
                    return { x, y };
                }

                pos.x += context.layout.cellSize().x;
            }

            pos.x = mapRect.left;
            pos.y += context.layout.cellSize().y;
        }

        return { -1, -1 }; // any negative values work here
    }

    const sf::Vector2f
        Map::mapPosToScreenPos(const Context & context, const MapPos_t & mapPos) const
    {
        return (
            util::position(context.layout.mapRect()) +
            (context.layout.cellSize() * sf::Vector2f{ mapPos }));
    }

    const std::vector<MapCell> Map::surroundingCellsHorizVert(const MapPos_t & pos) const
    {
        std::vector<MapCell> cells;

        if (const MapPos_t posAbove(pos.x, (pos.y - 1)); isPosValid(posAbove))
        {
            cells.push_back(cell(posAbove));
        }

        if (const MapPos_t posBelow(pos.x, (pos.y + 1)); isPosValid(posBelow))
        {
            cells.push_back(cell(posBelow));
        }

        if (const MapPos_t posRight((pos.x + 1), pos.y); isPosValid(posRight))
        {
            cells.push_back(cell(posRight));
        }

        if (const MapPos_t posLeft((pos.x - 1), pos.y); isPosValid(posLeft))
        {
            cells.push_back(cell(posLeft));
        }

        return cells;
    }

    const std::vector<MapCell> Map::surroundingCellsAll(const MapPos_t & pos) const
    {
        std::vector<MapCell> cells;

        for (int y(pos.y - 1); y <= (pos.y + 1); ++y)
        {
            for (int x(pos.x - 1); x <= (pos.x + 1); ++x)
            {
                const MapPos_t position(x, y);
                if (position == pos)
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
