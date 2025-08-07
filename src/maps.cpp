// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// maps.cpp
//
#include "maps.hpp"

#include "animation-manager.hpp"
#include "campfire.hpp"
#include "check-macros.hpp"
#include "context.hpp"
#include "inferno.hpp"
#include "map-display.hpp"
#include "monster-manager.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "smoke.hpp"
#include "sparkle-particle.hpp"
#include "tile-image-enum.hpp"

namespace castlecrawl
{
    Maps::Maps()
        : m_maps{}
        , m_currentIter{ std::end(m_maps) }
    {}

    void Maps::setup(const Context & t_context)
    {
        load(t_context);
        verify();
    }

    void Maps::change(const Context & t_context, MapName t_mapName, const MapPos_t & t_pos)
    {
        unloadCreatures(t_context);
        unloadAnimations(t_context);

        m_currentIter = std::find_if(std::begin(m_maps), std::end(m_maps), [&](const Map & map) {
            return (map.name() == t_mapName);
        });

        M_CHECK(
            (m_currentIter != std::end(m_maps)),
            "Tried to change to an invalid map named \"" << toString(t_mapName) << "\"");

        t_context.map_display.load(t_context);
        t_context.player_display.position(t_context, t_pos);

        loadCreatures(t_context);
        loadAnimations(t_context);
    }

    void Maps::loadCreatures(const Context & t_context)
    {
        const sf::Vector2i size = current().size();
        for (int y(0); y < size.y; ++y)
        {
            for (int x(0); x < size.x; ++x)
            {
                const MapPos_t pos{ x, y };
                const char ch = current().cell(pos).object_char;

                if ((ch == ' ') || (ch == '.'))
                {
                    continue;
                }

                if (isTileImageMonster(charToTileImage(ch)))
                {
                    t_context.monsters.add(t_context, pos, ch);
                }
                else if (isTileImageNpc(charToTileImage(ch)))
                {
                    t_context.npcs.add(t_context, pos, ch);
                }
            }
        }
    }

    void Maps::unloadCreatures(const Context & t_context)
    {
        t_context.monsters.reset();
        t_context.npcs.reset();
    }

    void Maps::loadAnimations(const Context & t_context)
    {
        const sf::Vector2i size = current().size();
        for (int y(0); y < size.y; ++y)
        {
            for (int x(0); x < size.x; ++x)
            {
                const MapPos_t pos{ x, y };
                const char ch = current().cell(pos).object_char;

                if ((ch == ' ') || (ch == '.'))
                {
                    continue;
                }

                if (tileImageToChar(TileImage::Campfire) == ch)
                {
                    t_context.anim.campfire().add(t_context, pos);
                }
                else if (tileImageToChar(TileImage::Inferno) == ch)
                {
                    t_context.anim.inferno().add(t_context, pos);
                }
                else if (tileImageToChar(TileImage::Coins) == ch)
                {
                    t_context.anim.sparkle().add(t_context, pos);
                }
            }
        }
    }

    void Maps::unloadAnimations(const Context & t_context)
    {
        t_context.anim.clear();
    }

    void Maps::forceMapForEditting(const Context & t_context, const Map t_map)
    {
        unloadCreatures(t_context);
        unloadAnimations(t_context);

        *m_currentIter = t_map;

        t_context.map_display.load(t_context);

        loadCreatures(t_context);
        loadAnimations(t_context);
    }

    void Maps::load(const Context & t_context)
    {
        m_maps.clear();

        // clang-format off
        m_maps.emplace_back(
            MapName::Level_1_Cell,
            t_context,
            Floor::Stone,
            MapChars_t {
                "...........",
                "...........",
                "...    G...",
                "...     ...",
                "...  a  ...",
                "...     ...",
                "...~~~  ...",
                "..... .....",
                "..... .....",
                ".....d....."
             },
            MapTransitions_t {
                { { 5, 10 }, MapName::Level_1_CellBlock, { 5, 1 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_CellBlock,
            t_context,
            Floor::Wood,
            MapChars_t {
                ".....d............................",
                "..... ............................",
                "..... ........................   I",
                "..... ........................ ...",
                ".....                          ...",
                "..... ........d...........d.......",
                "..... ........ ........... .......",
                "..... ........ ........... .......",
                "...     ....     .     .     .....",
                "...    b....     .     d     .....",
                "...   bb....     .     .     .....",
                "... ..........d.....d.......d.....",
                "... ........     .     .     .....",
                "... ........b    d  \x85  .     .....",
                "... ........bb   .     .     .....",
                "...    ...................d.......",
                "...... .....     .     .b    .....",
                "...... .....  \xE4  D     d     .....",
                "...... .....~    .     .     .....",
                "...... ...........................",
                "......d..........................."
                },
            MapTransitions_t {
                { { 5, -1 }, MapName::Level_1_Cell,  { 5, 8 } },
                { { 6, 21 }, MapName::Level_1_MainHall,  { 16, 1 } },
                { { 34, 2 }, MapName::Level_1_Basement, { 1, 2 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_MainHall,
            t_context,
            Floor::Wood,
            MapChars_t {
                "................d.................",
                "................ .................",
                "................ .................",
                ".............       ..............",
                ".....    ....       ......       d",
                ".....       D       ......b bbb...",
                ".....c   ....       ......   bb...",
                ".............       ......    b...",
                ".............       ......     ...",
                ".............       d          ...",
                ".............       ..............",
                "..          d       ..............",
                "..b      ....       ..............",
                "..bb     ....       ..............",
                "..bbb    ....       ......b    b..",
                "..b      ....       ......      ..",
                "..          d       D           ..",
                "..       ....       ......      ..",
                "..     bb....       ......b    b..",
                ".............       ..............",
                "................ .................",
                "................ .................",
                "................I................."
                },
            MapTransitions_t {
                { { 16, -1 }, MapName::Level_1_CellBlock,  { 6, 19 } },
                { { 16, 23 }, MapName::Level_1_BoilerRoom, { 2,  0 } },
                { { 34, 4 }, MapName::Level_1_HiddenPassage, { 1,  1 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_BoilerRoom,
            t_context,
            Floor::Stone,
            MapChars_t {
                "..i..........................",
                ".. ..........................",
                ".. ....ll  llllllll..........",
                ".. ....  l  lllllll..........",
                ".. ....b    ll  bbb.  bb.....",
                ".. ....      l   bb.   b.....",
                ".. .......        b.    .....",
                "..       .         .    .....",
                "........ .......D...    .....",
                "........ .              .....",
                "........d.              .....",
                "....                    .....",
                "....            .............",
                "d               . bbggggggg..",
                "....            d   ggg......",
                "....            .   ggg......",
                "............Z................",
                ".......l  b     .............",
                ".......bb      b.............",
                ".......bbbbllbbb.............",
                ".............................",
                "............................."
                },
            MapTransitions_t {
                { { 2,  -1 }, MapName::Level_1_MainHall, { 16, 22 } },
                { { -1,  13 }, MapName::Level_1_LavaGatehouse, { 15, 14 } }
                }
            );
        
        m_maps.emplace_back(
            MapName::Level_1_HiddenPassage,
            t_context,
            Floor::Wood,
            MapChars_t {
                "...................d.......",
                "d     ............. .......",
                "..... ............. .......",
                "..... ............. .......",
                "..... ............. .......",
                "..... ...                  ",
                "..... ... .................",
                "..... ... .................",
                "...b      .................",
                "...bb     .................",
                ".......   .................",
                "...c  D   .................",
                ".......d...................",
                "....... .....     bb.......",
                "....... .....   . bb.......",
                "....... .....   .   .......",
                ".......         ...........",
                ".............    ..........",
                ".............   b..........",
                "..........................."
                },
            MapTransitions_t {
                { { -1, 1 }, MapName::Level_1_MainHall,  { 32, 4 } },
                { { 27, 5 }, MapName::Level_1_CoffinRoom, { 0,  9 } },
                { { 19, -1 }, MapName::Level_1_LakeStronghold, { 13,  21 } }
                }
            );

        m_maps.emplace_back( 
            MapName::Level_1_CoffinRoom,
            t_context,
            Floor::Stone,
            MapChars_t {
                ".................................",
                ".................................",
                "...................    kk........",
                "........kkk........     k........",
                "........   .......... ...........",
                "....k      .......... ...........",
                "....... ............. ...........",
                "....... ............. ...........",
                ".......D............. ...........",
                "        D             ...........",
                ".......D.........................",
                "....... .........................",
                "....... .........................",
                "....... .........................",
                "....... .........................",
                "..           ....................",
                "..k          ....................",
                "..kk         ....................",
                "..kkk k    kk....................",
                ".................................",
                "................................."
                },
            MapTransitions_t {
                { { -1, 9 }, MapName::Level_1_HiddenPassage, { 26, 5 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_LakeStronghold,
            t_context,
            Floor::Stone,
            MapChars_t {
                "ggggg.........................ggggggggggg",
                "ggg  .......b          .......  ggggggggg",
                "gg   .......           .......        ggg",
                "g    ....bb.b          d     d          g",
                "..d......  ....        ....d........b   g",
                ".. ......     d        ....        .bb  g",
                ".. ......   ...        ....        ...  g",
                ".. ......   .      ........          .  g",
                "..      d   .      ........          . gg",
                ".....d....  .      ......b.          . gg",
                "..... ....  .   ......... .d.....    .  g",
                "..... .......   d    ....       .    .  g",
                "..... .......   .    ....       .    .  g",
                "..... .......   .    ....       ......  g",
                "g     .......   .    ....       ....b  gg",
                "g         .......  bb....       ....b ggg",
                "gg   .... .......  bc....b      ....b  gg",
                "ggg  .... ...............bb     .........",
                "gc   .... ...............bbb    .........",
                "......... ...............................",
                "......... ...............................",
                ".........     ...........................",
                ".............d..........................."
                },
            MapTransitions_t {{ { 13, 23 }, MapName::Level_1_HiddenPassage, { 19, 1 } }}
            );

        m_maps.emplace_back(
            MapName::Level_1_LavaGatehouse,
            t_context,
            Floor::Stone,
            MapChars_t {
                "lllllllllllllllll",
                "lllllllllllllllll",
                "lllllllllllllllll",
                "llll     lll  All",
                "ll             ll",
                "ll              l",
                "lA .....d.....  l",
                "lA .         .  l",
                "ll .         . Al",
                "ll .b        .  l",
                "ll .bb       .hHh",
                "lhh..... .....hch",
                "llhhhhh. .hhhhhhh",
                "ll....h. ........",
                "ll   .h.        d",
                "l    ... ........",
                "l    d   .hhhhhhh",
                "l    .....  bbhhh",
                "lA            hhl",
                "lllll      Alllll",
                "llllllllll llllll"
                },
            MapTransitions_t {
                { { 17,  14 }, MapName::Level_1_BoilerRoom, { 1, 13 } },
                { { 10,  21 }, MapName::Level_1_LavaHiddenPath, { 24, 0 } }
            }
            );

        m_maps.emplace_back(
            MapName::Level_1_LavaHiddenPath,
            t_context,
            Floor::Stone,
            MapChars_t {
                "llllllllllllllllllllllll llllllllllllllll",
                "llllllllllllllllllllllll llllllllllllllll",
                "llllllllllllllllllllllll llllllllllllllll",
                "llllllllllllllllllllllll   Alllllllllllll",
                "llllllllllllllllllllllll    Allllllllllll",
                "lllllllllllllllllllllllll    llllllllllll",
                "llllllllllllllllllll    l   lllllllllllll",
                "llllllllllllllllllll ll ll  lllllllllllll",
                "llllllllllllllllllll  l  l   llllllllllll",
                "lllllllllllllllllllll ll    Allllllllllll",
                "llllllllllllllllllll   llllllllllllllllll",
                "lllllllllllllllllllc 9 clllllllllllllllll",
                "llllllllllllllllllll   llllllllllllllllll",
                "lllllllllllllllllllllclllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                "lllllllllllllllllllllllllllllllllllllllll",
                },
            MapTransitions_t {{ { 24,  -1 }, MapName::Level_1_LavaGatehouse, { 10, 20 } }}
            );

        m_maps.emplace_back(
            MapName::Level_1_Basement,
            t_context,
            Floor::Stone,
            MapChars_t {
                "...............",
                "...............",
                "i    bZ hhhhh..",
                "....... h   h..",
                "....c . h h h..",
                ".... \x85. h6h h..",
                "....  . hhh h..",
                "....hD.     h..",
                "..k   hhhhh h..",
                "..k h       h..",
                "...............",
                "...............",
                },
            MapTransitions_t {{ { -1,  2 }, MapName::Level_1_CellBlock,  { 32, 2 } }}
            );

        // clang-format on

        m_currentIter = std::begin(m_maps);
    }

    void Maps::verify() const
    {
        M_CHECK(!m_maps.empty(), "No maps were loaded!");

        for (const Map & map : m_maps)
        {
            M_CHECK(
                !map.transitions().empty(),
                "Map \"" << toString(map.name()) << "\" has no transitions!");

            for (const MapTransition & transition : map.transitions())
            {
                const auto foundIter =
                    std::find_if(std::begin(m_maps), std::end(m_maps), [&](const Map & m) {
                        return (m.name() == transition.to_name);
                    });

                M_CHECK(
                    (foundIter != std::end(m_maps)),
                    "Map \"" << toString(map.name())
                             << "\" has invalid to_name transition to unknown map named \""
                             << toString(transition.to_name) << "\"");
            }
        }
    }

} // namespace castlecrawl
