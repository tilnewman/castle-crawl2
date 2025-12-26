#ifndef MAPTYPES_HPP_INCLUDED
#define MAPTYPES_HPP_INCLUDED
//
// map.hpp
//
#include "json-wrapper.hpp"

#include <cmath>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

namespace castlecrawl
{
    using MapPos_t   = sf::Vector2i;
    using MapChars_t = std::vector<std::string>;

    static inline const MapPos_t invalidMapPos = { -1, -1 }; // any two negative values work here

    // template <typename T>
    // inline void to_json(nlohmann::json & j, const sf::Vector2<T> & v)
    //{
    //     j = nlohmann::json{ { "x", v.x }, { "y", v.y } };
    // }
    //
    // template <typename T>
    // inline void from_json(const nlohmann::json & j, sf::Vector2f & v)
    //{
    //     j.at("x").get_to(v.x);
    //     j.at("y").get_to(v.y);
    // }
    //
    // inline void to_json(nlohmann::json & j, const MapPos_t & mp)
    //{
    //     j = nlohmann::json{ { "x", mp.x }, { "y", mp.y } };
    // }
    //
    // inline void from_json(const nlohmann::json & j, MapPos_t & mp)
    //{
    //     j.at("x").get_to(mp.x);
    //     j.at("y").get_to(mp.y);
    // }

    struct MapCell
    {
        // these default values are safe where needed and invalid where needed -don't change
        MapPos_t position = invalidMapPos;
        char object_char  = '.';
        char floor_char   = ' ';
    };

    inline void to_json(nlohmann::json & j, const MapCell & mc)
    {
        j = nlohmann::json{ { "position_x", mc.position.x },
                            { "position_y", mc.position.y },
                            { "object_char", mc.object_char },
                            { "floor_char", mc.floor_char } };
    }

    inline void from_json(const nlohmann::json & j, MapCell & mc)
    {
        j.at("position_x").get_to(mc.position.x);
        j.at("position_y").get_to(mc.position.y);
        j.at("object_char").get_to(mc.object_char);
        j.at("floor_char").get_to(mc.floor_char);
    }

    [[nodiscard]] inline int distance(const MapPos_t & t_posA, const MapPos_t & t_posB) noexcept
    {
        return (std::abs(t_posB.x - t_posA.x) + std::abs(t_posB.y - t_posA.y));
    }

    [[nodiscard]] inline int distance(const MapCell & t_cellA, const MapCell & t_cellB) noexcept
    {
        return distance(t_cellA.position, t_cellB.position);
    }

    struct PositionDistance
    {
        PositionDistance(const MapPos_t & t_mapPos, const int t_distance)
            : position{ t_mapPos }
            , distance{ t_distance }
        {}

        MapPos_t position{ invalidMapPos }; // both must be negative to be invalid
        int distance{ 0 };
    };

    using Map_t = std::vector<std::vector<MapCell>>;

    enum class Floor
    {
        Dirt,
        Stone,
        Wood
    };

    [[nodiscard]] constexpr std::string_view toString(const Floor t_floor) noexcept
    {
        if (t_floor == Floor::Dirt)
        {
            return "Dirt";
        }
        else if (t_floor == Floor::Stone)
        {
            return "Stone";
        }
        else
        {
            return "Wood";
        }
    }

    using VertVec_t = std::vector<sf::Vertex>;

    // used for indexing so keep unsigned
    enum class MapName : std::size_t
    {
        Level_1_Cell = 0,
        Level_1_CellBlock,
        Level_1_MainHall,
        Level_1_BoilerRoom,
        Level_1_HiddenPassage,
        Level_1_CoffinRoom,
        Level_1_LakeStronghold,
        Level_1_LavaGatehouse,
        Level_1_LavaHiddenPath,
        Level_1_Basement,
        Level_1_Forest,
        Count
    };

    constexpr std::string_view toString(const MapName t_name) noexcept
    {
        // clang-format off
        switch (t_name)
        {
            case MapName::Level_1_Cell:             { return "Level_1_Cell"; }
            case MapName::Level_1_CellBlock:        { return "Level_1_CellBlock"; }
            case MapName::Level_1_MainHall:         { return "Level_1_MainHall"; }
            case MapName::Level_1_BoilerRoom:       { return "Level_1_BoilerRoom"; }
            case MapName::Level_1_HiddenPassage:    { return "Level_1_HiddenPassage"; }
            case MapName::Level_1_CoffinRoom:       { return "Level_1_CoffinRoom"; }
            case MapName::Level_1_LakeStronghold:   { return "Level_1_LakeStronghold"; }
            case MapName::Level_1_LavaGatehouse:    { return "Level_1_LavaGatehouse"; }
            case MapName::Level_1_LavaHiddenPath:   { return "Level_1_LavaHiddenPath"; }
            case MapName::Level_1_Basement:         { return "Level_1_Basement"; }
            case MapName::Level_1_Forest:           { return "Level_1_Forest"; }
            case MapName::Count:
            default:                                { return "(unknown_MapName)"; }
        }
        // clang-format on
    }

    inline std::ostream & operator<<(std::ostream & t_os, const MapName t_mapName)
    {
        t_os << toString(t_mapName);
        return t_os;
    }

    struct MapTransition
    {
        MapPos_t from_pos{ invalidMapPos };
        MapName to_name{ MapName::Level_1_Cell }; // anything works here
        MapPos_t to_pos{ invalidMapPos };
    };

    using MapTransitions_t = std::vector<MapTransition>;

    inline void to_json(nlohmann::json & j, const MapTransition & mt)
    {
        j = nlohmann::json{ { "from_pos_x", mt.from_pos.x },
                            { "from_pos_y", mt.from_pos.y },
                            { "to_name", mt.to_name },
                            { "to_pos_x", mt.to_pos.x },
                            { "to_pos_y", mt.to_pos.y } };
    }

    inline void from_json(const nlohmann::json & j, MapTransition & mt)
    {
        j.at("from_pos_x").get_to(mt.from_pos.x);
        j.at("from_pos_y").get_to(mt.from_pos.y);
        j.at("to_name").get_to(mt.to_name);
        j.at("to_pos_x").get_to(mt.to_pos.x);
        j.at("to_pos_y").get_to(mt.to_pos.y);
    }

} // namespace castlecrawl

#endif // MAPTYPES_HPP_INCLUDED
