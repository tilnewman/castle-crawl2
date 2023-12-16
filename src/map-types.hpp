#ifndef MAPTYPES_HPP_INCLUDED
#define MAPTYPES_HPP_INCLUDED
//
// map.hpp
//
#include <string>
#include <string_view>
#include <vector>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

namespace castlecrawl
{
    using MapPos_t   = sf::Vector2i;
    using MapChars_t = std::vector<std::string>;

    struct MapCell
    {
        // these default values are safe where needed and invalid where needed -don't change
        MapPos_t position = { -1, -1 };
        char object_char  = '.';
        char floor_char   = ' ';
    };

    using Map_t = std::vector<std::vector<MapCell>>;

    enum class Floor
    {
        Dirt,
        Stone,
        Wood
    };

    using VertVec_t = std::vector<sf::Vertex>;

    enum class MapName
    {
        Level_1_Cell,
        Level_1_CellBlock,
        Level_1_SecretCells,
        Level_1_CellJunction,
        Level_1_CellsEnd,
        Level_1_MainHall,
        Level_1_BoilerRoom,
        Level_1_HiddenPassage,
        Level_1_CoffinRoom,
        Level_1_LakeStronghold,
        Level_1_LavaGatehouse
    };

    inline constexpr std::string_view toString(const MapName name) noexcept
    {
        // clang-format off
        switch (name)
        {
            case MapName::Level_1_Cell:             { return "Level_1_Cell"; }
            case MapName::Level_1_CellBlock:        { return "Level_1_CellBlock"; }
            case MapName::Level_1_SecretCells:      { return "Level_1_SecretCells"; }
            case MapName::Level_1_CellJunction:     { return "Level_1_CellJunction"; }
            case MapName::Level_1_CellsEnd:         { return "Level_1_CellsEnd"; }
            case MapName::Level_1_MainHall:         { return "Level_1_MainHall"; }
            case MapName::Level_1_BoilerRoom:       { return "Level_1_BoilerRoom"; }
            case MapName::Level_1_HiddenPassage:    { return "Level_1_HiddenPassage"; }
            case MapName::Level_1_CoffinRoom:       { return "Level_1_CoffinRoom"; }
            case MapName::Level_1_LakeStronghold:   { return "Level_1_LakeStronghold"; }
            case MapName::Level_1_LavaGatehouse:    { return "Level_1_LavaGatehouse"; }
            default:                                { return "(unknown_MapName)"; }
        }
        // clang-format on
    }

    inline std::ostream & operator<<(std::ostream & os, const MapName mapName)
    {
        os << toString(mapName);
        return os;
    }

    struct MapTransition
    {
        MapPos_t from_pos{ -1, -1 };              // both must be negative to be invalid
        MapName to_name{ MapName::Level_1_Cell }; // anything works here
        MapPos_t to_pos{ -1, -1 };                // both must be negative to be invalid
    };

    using MapTransitions_t = std::vector<MapTransition>;

} // namespace castlecrawl

#endif // MAPTYPES_HPP_INCLUDED
