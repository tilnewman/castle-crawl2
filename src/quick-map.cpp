// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// quick-map.cpp
//
#include "quick-map.hpp"

#include "check-macros.hpp"

#include <iostream>
#include <string>

namespace castlecrawl
{

    QuickMap::QuickMap(const GameConfig & t_config, const MapChars_t & t_mapChars)
        : m_mapChars{ t_mapChars }
    {
        convertQuickMapToRealMap(t_config);
    }

    char QuickMap::getChar(const int t_x, const int t_y) const
    {
        if (empty() || !isPosValid({ t_x, t_y }))
        {
            return '.';
        }
        else
        {
            return m_mapChars.at(static_cast<std::size_t>(t_y)).at(static_cast<std::size_t>(t_x));
        }
    }

    void QuickMap::dumpToConsole() const
    {
        for (const std::string & row : m_mapChars)
        {
            std::cout << row << std::endl;
        }
    }

    void QuickMap::convertQuickMapToRealMap(const GameConfig & t_config)
    {
        convertQuickMapToRealMap_VerifySize(t_config);
        convertQuickMapToRealMap_Walls();
        convertQuickMapToRealMap_WallCorners();
    }

    void QuickMap::convertQuickMapToRealMap_VerifySize(const GameConfig &) const
    {
        M_CHECK(!empty(), "QuickMap constructor given an empty map!");

        const std::size_t rowLength = m_mapChars.front().size();
        for (const std::string & row : m_mapChars)
        {
            M_CHECK(
                (rowLength == row.size()),
                "QuickMap constrcutor given a map with rows of different lengths!");
        }
    }

    void QuickMap::convertQuickMapToRealMap_Walls()
    {
        if (empty())
        {
            return;
        }

        auto isNotObs = [](const char ch) {
            return ((ch != '.') && (ch != 'Y') && (ch != 'X') && (ch != 'r'));
        };

        const MapPos_t mapSize = size();

        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const char ch{ getChar(x, y) };

                if (ch != '.')
                {
                    continue;
                }

                // check all four sides
                const char up{ getChar(x, y - 1) };
                const char down{ getChar(x, y + 1) };
                const char left{ getChar(x - 1, y) };
                const char right{ getChar(x + 1, y) };

                if (isNotObs(left) || isNotObs(right))
                {
                    setChar(x, y, 'Y');
                    continue;
                }
                else if (isNotObs(up) || isNotObs(down))
                {
                    setChar(x, y, 'X');
                    continue;
                }

                // check all four corners
                const char topLeft{ getChar(x - 1, y - 1) };
                const char topRight{ getChar(x + 1, y - 1) };
                const char botLeft{ getChar(x - 1, y + 1) };
                const char botRight{ getChar(x + 1, y + 1) };

                if (isNotObs(topLeft) || isNotObs(topRight) || isNotObs(botLeft) ||
                    isNotObs(botRight))
                {
                    // 'X' works here too but don't make it random so maps always look the same
                    setChar(x, y, 'Y');
                    continue;
                }
            }
        }
    }

    void QuickMap::convertQuickMapToRealMap_WallCorners()
    {
        if (empty())
        {
            return;
        }

        const MapPos_t mapSize(size());

        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const char ch{ getChar(x, y) };

                if ((ch != 'Y') && (ch != 'X'))
                {
                    continue;
                }

                const char up{ getChar(x, y - 1) };
                const char down{ getChar(x, y + 1) };
                const char left{ getChar(x - 1, y) };
                const char right{ getChar(x + 1, y) };

                if (ch == 'Y')
                {
                    if ((left == 'X') || (right == 'X'))
                    {
                        setChar(x, y, 'z');
                    }

                    if ((down == 'Y') && ((up == ' ') || (up == '.')))
                    {
                        setChar(x, y, 'z');
                    }

                    if ((up == 'Y') && ((down == ' ') || (down == '.')))
                    {
                        setChar(x, y, 'z');
                    }
                }
                else //'X'
                {
                    if ((up == 'Y') || (down == 'Y'))
                    {
                        setChar(x, y, 'z');
                    }

                    if ((left == 'X') && ((right == ' ') || (right == '.')))
                    {
                        setChar(x, y, 'z');
                    }

                    if ((right == 'X') && ((left == ' ') || (left == '.')))
                    {
                        setChar(x, y, 'z');
                    }
                }

                if (getChar(x, y) != 'z')
                {
                    continue;
                }

                if ((down == 'Y') || (down == 'X'))
                {
                    if ((right == 'Y') || (right == 'X'))
                    {
                        setChar(x, y, 'x');
                    }
                    else
                    {
                        setChar(x, y, 'y');
                    }
                }
            }
        }
    }

} // namespace castlecrawl
