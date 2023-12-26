// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// maps.cpp
//
#include "maps.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "enemy.hpp"
#include "map-display.hpp"
#include "player-display.hpp"

namespace castlecrawl
{
    Maps::Maps()
        : m_maps()
        , m_currentIter(std::end(m_maps))
    {}

    void Maps::setup(const Context & context)
    {
        load(context);
        verify();
    }

    void Maps::change(const Context & context, MapName mapName, const MapPos_t & pos)
    {
        unloadEnemies(context);

        m_currentIter = std::find_if(std::begin(m_maps), std::end(m_maps), [&](const Map & map) {
            return (map.name() == mapName);
        });

        M_CHECK(
            (m_currentIter != std::end(m_maps)),
            "Tried to change to an invalid map named \"" << toString(mapName) << "\"");

        loadEnemies(context, *m_currentIter);
        context.map_display.load(context);
        context.player_display.position(context, pos);
    }

    void Maps::forceMapForEditting(const Map map) { *m_currentIter = map; }

    void Maps::load(const Context & context)
    {
        m_maps.clear();

        // clang-format off
        m_maps.emplace_back(
            MapName::Level_1_Cell,
            context,
            Floor::Stone,
            MapChars_t {
                "...........",
                "...........",
                "...     ...",
                "...     ...",
                "...     ...",
                "...     ...",
                "...     ...",
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
            context,
            Floor::Wood,
            MapChars_t {
                ".....d............................",
                "..... ............................",
                "..... ........................    ",
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
                "... ........b    d     .     .....",
                "... ........bb   .     .     .....",
                "...    ...................d.......",
                "...... .....3    .     .b    .....",
                "...... .....     D     d     .....",
                "...... .....c    .     .     .....",
                "...... ...........................",
                "......d..........................."
                },
            MapTransitions_t {
                { { 5, -1 }, MapName::Level_1_Cell,  { 5, 8 } },
                { { 6, 21 }, MapName::Level_1_MainHall,  { 16, 1 } },
                { { 34, 2 }, MapName::Level_1_SecretCells, { 0, 3 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_SecretCells,
            context,
            Floor::Wood,
            MapChars_t {
                ".........................................",
                ".........................................",
                ".........................................",
                "                                         ",
                ".....d.........d.........d.........d.....",
                "..       ...       ...       ...       ..",
                "..       ...       ...       ...       ..",
                "..       ...       ...       ...       ..",
                "..       ...       ...       ...       ..",
                "..       ...       ...       ...       ..",
                "..       ...       ...       ...       ..",
                "..       ...       ...       ...       ..",
                ".......D.........D.........D.........d...",
                "....... ......... ......... ......... ...",
                "....... ......... ......... ......... ...",
                "...k                                  ...",
                "..........kk kk..........d...............",
                "......................b     .............",
                "......................bb . b.............",
                "......................bbb.bb.............",
                "........................................."
                },
            MapTransitions_t {
                { { -1, 3 }, MapName::Level_1_CellBlock,  { 33, 2 } },
                { { 41, 3 }, MapName::Level_1_CellJunction,  { 0, 4 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_CellJunction,
            context,
            Floor::Wood,
            MapChars_t {
                ".........................................",
                ".........................................",
                ".........................................",
                ".........................                ",
                "            .............    ............",
                "..........  .............    ............",
                "..........  ........    .    ............",
                "..........  ........    .    ............",
                "..........  ........    .    ............",
                "..........  ........         ............",
                "..........         d         ............",
                ".....    d         d      ...............",
                "..... ..............      ...............",
                "..... ..............      ...............",
                "..... ..............      .........bbbb..",
                "..... ..............      d    ....bb  ..",
                "...    b...................... ....    ..",
                "...   .b...................... ....    ..",
                "...   .b......................    d    ..",
                "...   .b...........................    ..",
                "...................................    ..",
                ".........................................",
                "........................................."
                },
            MapTransitions_t {
                { { -1, 4 }, MapName::Level_1_SecretCells,  { 40, 3 } },
                { { 41, 3 }, MapName::Level_1_CellsEnd, { 0, 8 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_CellsEnd,
            context,
            Floor::Wood,
            MapChars_t {
                ".........................................",
                "...............      b...................",
                "...............      b...................",
                "...............   .......................",
                "...............   .bbb...................",
                "...........       .bbb...................",
                "...........       .   ...................",
                "...........           ...................",
                "          d      ........................",
                "...........         .....................",
                "...........         .....................",
                "................    .....................",
                "................    d    ................",
                "................    .... .....bb   ......",
                "................    .... .....b    ......",
                "........................ .....     ......",
                "........................     d     ......",
                "..............................    b......",
                "..............................   bb......",
                ".........................................",
                ".........................................",
                ".........................................",
                "........................................."
                },
            MapTransitions_t {
                { { -1, 8 }, MapName::Level_1_SecretCells,  { 40, 3 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_MainHall,
            context,
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
                "................s................."
                },
            MapTransitions_t {
                { { 16, -1 }, MapName::Level_1_CellBlock,  { 6, 19 } },
                { { 16, 23 }, MapName::Level_1_BoilerRoom, { 2,  0 } },
                { { 34, 4 }, MapName::Level_1_HiddenPassage, { 1,  1 } }
                }
            );

        m_maps.emplace_back(
            MapName::Level_1_BoilerRoom,
            context,
            Floor::Stone,
            MapChars_t {
                "..S..........................",
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
                "d               . bbwwwwwww..",
                "....            d   www......",
                "....            .   www......",
                "............ ................",
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
            context,
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
            context,
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
            context,
            Floor::Stone,
            MapChars_t {
                "wwwww.........................wwwwwwwwwww",
                "www  .......b          .......  wwwwwwwww",
                "ww   .......           .......        www",
                "w    ....bb.b          d     d          w",
                "..d......  ....        ....d........b   w",
                ".. ......     d        ....        .bb  w",
                ".. ......   ...        ....        ...  w",
                ".. ......   .      ........          .  w",
                "..      d   .      ........          . ww",
                ".....d....  .      ......b.          . ww",
                "..... ....  .   ......... .d.....    .  w",
                "..... .......   d    ....       .    .  w",
                "..... .......   .    ....       .    .  w",
                "..... .......   .    ....       ......  w",
                "w     .......   .    ....       ....b  ww",
                "w         .......  bb....       ....b www",
                "ww   .... .......  bc....b      ....b  ww",
                "www  .... ...............bb     .........",
                "wc   .... ...............bbb    .........",
                "......... ...............................",
                "......... ...............................",
                ".........     ...........................",
                ".............d..........................."
                },
            MapTransitions_t {{ { 13, 23 }, MapName::Level_1_HiddenPassage, { 19, 1 } }}
            );

        m_maps.emplace_back(
            MapName::Level_1_LavaGatehouse,
            context,
            Floor::Stone,
            MapChars_t {
                "lllllllllllllllll",
                "lllllllllllllllll",
                "lllllllllllllllll",
                "llll     lll   ll",
                "ll             ll",
                "ll              l",
                "l  .....d.....  l",
                "l  .         .  l",
                "ll .         .  l",
                "ll .         .  l",
                "ll .         .rrr",
                "lrr..... .....rrr",
                "llrrrrr. .rrrrrrr",
                "ll....r. ........",
                "ll   .r.        d",
                "l    ... ........",
                "l    d   .rrrrrrr",
                "l    .....    rrr",
                "l             rrl",
                "lllll       lllll",
                "llllllllll llllll"
                },
            MapTransitions_t {
                { { 17,  14 }, MapName::Level_1_BoilerRoom, { 1, 13 } },
                { { 10,  21 }, MapName::Level_1_LavaHiddenPath, { 24, 0 } }
            }
            );

        m_maps.emplace_back(
            MapName::Level_1_LavaHiddenPath,
            context,
            Floor::Stone,
            MapChars_t {
                "llllllllllllllllllllllll llllllllllllllll",
                "llllllllllllllllllllllll llllllllllllllll",
                "llllllllllllllllllllllll llllllllllllllll",
                "llllllllllllllllllllllll    lllllllllllll",
                "llllllllllllllllllllllll     llllllllllll",
                "lllllllllllllllllllllllll    llllllllllll",
                "llllllllllllllllllll    l   lllllllllllll",
                "llllllllllllllllllll ll ll  lllllllllllll",
                "llllllllllllllllllll  l  l   llllllllllll",
                "lllllllllllllllllllll ll     llllllllllll",
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

    void Maps::loadEnemies(const Context & context, Map & map) const
    {
        const sf::Vector2i size = map.size();

        for (int y(0); y < size.y; ++y)
        {
            for (int x(0); x < size.x; ++x)
            {
                const MapPos_t pos(x, y);
                const MapCell & cell = map.cell(pos);

                if (cell.object_char == '0')
                {
                    context.enemies.add({ context.random, Enemy::Snake, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '1')
                {
                    context.enemies.add({ context.random, Enemy::SnakeBag, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '2')
                {
                    context.enemies.add({ context.random, Enemy::Spider, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '3')
                {
                    context.enemies.add({ context.random, Enemy::Spiderweb, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '4')
                {
                    context.enemies.add({ context.random, Enemy::Goblin, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '5')
                {
                    context.enemies.add({ context.random, Enemy::GoblinBarrel, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '6')
                {
                    context.enemies.add({ context.random, Enemy::Bat, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '7')
                {
                    context.enemies.add({ context.random, Enemy::BatMask, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '8')
                {
                    context.enemies.add({ context.random, Enemy::Skeleton, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '9')
                {
                    context.enemies.add({ context.random, Enemy::SkeletonGrave, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == ':')
                {
                    context.enemies.add({ context.random, Enemy::Demon, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == ';')
                {
                    context.enemies.add({ context.random, Enemy::DemonDoor, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '[')
                {
                    context.enemies.add({ context.random, Enemy::Dragon, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == ']')
                {
                    context.enemies.add({ context.random, Enemy::DragonInferno, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '`')
                {
                    context.enemies.add({ context.random, Enemy::Wizard, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '~')
                {
                    context.enemies.add({ context.random, Enemy::WizardTomb, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '\'')
                {
                    context.enemies.add({ context.random, Enemy::Pixie, cell.position });
                    map.setObjectChar(pos, ' ');
                }
                else if (cell.object_char == '\"')
                {
                    context.enemies.add({ context.random, Enemy::PixieCup, cell.position });
                    map.setObjectChar(pos, ' ');
                }
            }
        }
    }

    void Maps::unloadEnemies(const Context & context) const { context.enemies.removeAll(); }

} // namespace castlecrawl
